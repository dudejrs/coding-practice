
/* Case 1 : 아래 함수 중 plumage와 airSpeedVelocity의 로직들을 다형성으로 분리하여*/


class Bird {

	constructor({name, type, numberOfCoconuts, voltage, isNailed}){
		this.name = name
		this.type = type;
		this.numberOfCoconuts = numberOfCoconuts
		this.voltage = voltage
		this.isNailed = isNailed
	}

	get plumage() {return "알 수 없다";}

	get airSpeedVelocity() { return null;}
}

class EuropeanSwallow extends Bird {

	get plumage() {
		return "보통이다"
	}

	get airSpeedVelocity() {
		return 35;
	}

}

class AfricanSwallow extends Bird {

	get plumage() {
		return (this.numberOfCoconuts > 2) ? "지쳤다" : "보통이다";
	}

	get airSpeedVelocity() {
		return 40 - 2 * this.numberOfCoconuts;
	}

}

class NorwegianBlueParrot extends Bird {

	get plumage() {
		return (this.voltage > 100) ? "그을렸다" : "예쁘다";
	}

	get airSpeedVelocity() {
		return (this.isNailed) ? 0 : 10 + this.voltage / 10;
	}

}


function createBird(bird){
	switch(bird.type){
		case '유럽 제비' :		 
			return new EuropeanSwallow(bird);
		case '아프리카 제비' : 
			return new AfricanSwallow(bird);
		case '노르웨이 파랑 엥무' :
			return new NorwegianBlueParrot(bird);
		default :
			return new Bird(bird);
	}
}


function plumages(birds){
	return new Map(birds.map(b => [b.name, plumage(b)]));
}

function speeds(birds){
	return new Map(birds.map(b => [b.name, airSpeedVelocity(b)]));
}

function plumage(bird){
	return new createBird(bird).plumage
}

function airSpeedVelocity(bird){
	return new createBird(bird).airSpeedVelocity;
}


birds = [ {name : 'bird1', type : '유럽 제비'},
	{name : 'bird2', type : '아프리카 제비', numberOfCoconuts : 0},
	{name : 'bird3', type : '노르웨이 파랑 엥무', isNailed : true, voltage : 100}];

console.log(plumages(birds));
console.log(speeds(birds));


/* Case 2 : 아래 함수 중 captaingHistoryRisk, hasChina, voyageProfitFactor의 조건부 로직들을 
다형성으로 분리하여라 
*/

class Rating {

	constructor(voyage, history){
		this.voyage = voyage
		this.history = history
	}

	get value(){
		const vpf = this.voyageProfitFactor;
		const vr = this.voyageRisk;
		const chr = this.captaingHistoryRisk;
		if (vpf * 3  > (vr+chr*2))
			return "A";
		else 
			return "B";
	}

	get voyageRisk() {
		let result =1;
		if (voyage.length > 4)
			result += 2;
		if (voyage.length > 8)
			result += voyage.length - 8;
		if(["중국","동인도"].includes(voyage.zone))
			result += 4;
		return Math.max(result, 0);
	}

	get captaingHistoryRisk (){
		let result = 1;
		if (history.length < 5)
			result +=4;
		result += history.filter(v=>v.profit<0).length;
		
		return Math.max(result,0);
	}

	get hasChina(){
		return history.some(v=> "중국" === v.zone);
	}

	get voyageProfitFactor(){
		let result = 2;
		if(voyage.zone === "중국") result += 1;
		if(voyage.zone === "동인도") result += 1;

		return result += this.voyageLengthProfitFactor;
	}

	get voyageLengthProfitFactor(){
		let result = 0; 
		if(history.length > 8) result +=1;
		if(history.length > 14) result -=1;
		return result;
	}

};

class ExperiencedChinaRating extends Rating {

	get captaingHistoryRisk() {
		let result = super.captaingHistoryRisk() - 2;
		return Math.max(result, 0)
	}

	get voyageProfitFactor(){
		return super.voyageProfitFactor() + 3 ; 
	}

	get voyageLengthProfitFactor(){
		let result = 0; 

		if(history.length > 10) result +=1;
		if(history.length > 12) result +=1;
		if(history.length > 18) result -=1;

		return result;
	}

};

function createRating(voyage, history){
	if(voyage.zone === "중국" && history.some(v=> "중국" === v.zone))
		return new ExperiencedChinaRating(voyage, history);
	return new Rating(voyage, history)
}


function rating(voyage, history){
	return new Rating(voyage,history).value;
}


const voyage = { zone : "서인도", length : 10};
const history = [
	{ zone : "동인도", profit : 5},
	{ zone : "서인도", profit : 15},
	{ zone : "중국", profit : -2},
	{ zone : "아프리카", profit : 7},
]
console.log(rating(voyage,history));