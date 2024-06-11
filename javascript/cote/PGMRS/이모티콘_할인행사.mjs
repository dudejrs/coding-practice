import {readFileSync} from 'fs'

const [N, M] = [40, 7]


class Result {
    constructor(subscribers, sales) {
        this.subscribers = subscribers
        this.sales = sales
    }
    
    static compare(r1, r2) {
        if (r1.subscribers != r2.subscribers) {
            return r1.subscribers < r2.subscribers
        }
        return r1.sales < r2.sales
    }
}

class Emoticon {
    constructor(price, rate) {
        this.price = price
        this.rate = rate
    }
    get amount() {
        return this.price * (1 - this.rate / 100)
    }
}

const RATIO = [10, 20, 30, 40]

function calculate(users, emoticons, discountRates) {
    emoticons = emoticons.map((price, i) => new Emoticon(price, discountRates[i])) 
    let [subscribers, sales] = [0, 0] 
    
    for (let [r, threshold] of users) {
        let amount = emoticons.filter(e => e.rate >= r)
            .reduce((acc, e) => acc + e.amount, 0)
        if (amount >= threshold) {
            subscribers += 1 
        } else {
            sales += amount
        }
    }
    
    return new Result(subscribers, sales)
}

function solve(users, emoticons) {
    let discountRates = []
    let ret = new Result(0, 0);
    
    function dfs(cur) {
        if (cur == emoticons.length) {
            let result = calculate(users, emoticons, discountRates)
            if(Result.compare(ret, result))  {
                ret = result
            }
            return
        }
        
        for (let ratio of RATIO) {
            discountRates.push(ratio)
            dfs(cur + 1)
            discountRates.pop()
        }
    }
    
    dfs(0)
    
    return [ret.subscribers, ret.sales];
}

(function main() {
	const [tc, ...data] = readFileSync('./data/이모티콘_할인행사.txt', {encoding : "utf-8"}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const users = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const emoticons = data[cur++].split(" ").map(i => parseInt(i)) 
		const results = data[cur++].split(" ").map(i => parseInt(i))
		console.log(results, solve(users, emoticons))
	}

})()