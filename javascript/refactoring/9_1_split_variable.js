/* 
Case1 : 값을 두번 대입받고 있는 acc를 두 변수로 분리하여라 
*/


function distanceTravelled (scenerio, time){
	let result;
	let primaryAcceleration = scenerio.primaryForce / scenario.mass;
	let primaryTime = Math.min(time, scenerio.delay);
	result = 0.5 * primaryAcceleration * primaryTime * primaryTime;
	
	let secondaryTime = time = scenerio.delay;
	if (secondaryTime > 0 ){
		let primaryVelocity = primaryAcceleration * scenerio.delay;
		let secondaryAcceleration = (scenerio.primaryForce + scenario.secondaryForce) / scenario.mass;
		result += primaryVelocity * secondaryTime + 0.5 * secondaryAcceleration * secondaryTime * secondaryTime;
	}
	return result
}


/* 
Case2 : 매개변수를 수정하고 있는 inputValue를 두변수로 나누어라 
 */

function discount(origininputValue, quantity){
	let result = origininputValue;
	if ( inputValue > 50) result = result -2;
	if ( quantity > 100 ) result = result -1;
	return result;
}

