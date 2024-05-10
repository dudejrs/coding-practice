import {readFileSync} from 'fs'

const MAX_CACHE_SIZE = 30
const MAX_CITIES_LENGTH = 100000

const CACHE_HIT = 1
const CACHE_MISS = 5

class Cache {
    static CACHE_HIT = 1
    static CACHE_MISS = 5

    constructor(size) {
        this.size = size
        this.data = new Map()
        this._time = 0
    }
    
    update(d) {
        if (this.data.has(d)) {
            this._time += Cache.CACHE_HIT
            this.data.set(d, this.time)
            return
        }
        
        this._time += Cache.CACHE_MISS
        this.data.set(d, this.time)
        
        if (this.data.size > this.size) {
            this.data.delete(this.eldest)  
        } 
    }
    
    get time() {
        return this._time
    }
    
    get eldest() {
    
        let [cur, cur_time] = [undefined, Number.MAX_VALUE]
        
        for (let [d, t] of this.data.entries()) {
            if (t < cur_time) {
                cur_time = t
                cur = d
            }
        }
       
        return cur
    }
}

function solve(cacheSize, cities) {
    const cache = new Cache(cacheSize)
    
    for (let city of cities) {
        cache.update(city.toLowerCase())
    }

    return cache.time;
}
function main() {
	const [tc, ...data] = readFileSync('data/LRU_캐시_실행시간.txt', {encoding : 'utf-8'}).split("\n")
	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const cacheSize = parseInt(data[cur++])
		const cities = data[cur++].split(" ")
		const answer = parseInt(data[cur++])	

		console.log(answer, solve(cacheSize, cities))
	}
}

main()