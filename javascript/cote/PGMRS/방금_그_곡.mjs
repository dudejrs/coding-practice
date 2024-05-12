import {readFileSync} from 'fs'

class Match {
    constructor(matched, played, index) {
        this.matched = matched
        this.played = played
        this.index = index
    }
}

class Song {
    static Token = /[AGFDCEB]#?/g
    
    constructor(start, end, name, melody) {
        this.length = Song.parseTime(end) - Song.parseTime(start)
        this.name = name
        this.melody = melody
    }
    
    static parseTime(time) {
        const nums = time.split(":")
            .map(i => parseInt(i))

        return parseInt(nums[0]) * 60 + parseInt(nums[1])
    }
    
    static convert(m) {
        const flats = ['A#', 'B#', 'C#', 'D#', 'F#', 'G#', 'E#']
        let cur = 0
        
        for (let c of flats) {
            m = m.replaceAll(c, cur++)
        }
        return m
    }
    
    static length(s) {
        if (!s) {
            return 0
        }   
        
        return s.match(Song.Token).length 
    }
    
    static matchAll(m, target) {
        target = Song.convert(target)
        m = Song.convert(m)
        
        return [...target.matchAll(m)]
    }
    
    match(m, i) {
        const tokens = Song.matchAll(m, this.m)
        const matched = tokens.length > 0 ? true : false
        
        return new Match(matched, this.length, i)
    }
    
    get m() {
        let s = ""
        while(Song.length(s) < this.length) {
            for (let token of this.melody.match(Song.Token)) {
                if (Song.length(s) == this.length) {
                    break
                }
                s += token
            }
        }
        
        return s
    }
}

function solve(m, musicinfos) {
    const songs = musicinfos.map(info => new Song(...info.split(",")))
    const matched = songs.map((song, i) => song.match(m, i))
        
    matched.sort((m1, m2) => {
        if (m1.matched != m2.matched) {
            return m1.matched ? -1 : 1
        }
        
        if (m1.played != m2.played) {
            return m2.played - m1.played
        }
        
        return m1.index - m2.index
    })
    
    if (matched[0].matched == 0) {
        return "(None)"
    }
    
    return songs[matched[0].index].name;
}

(function main() {

	const [tc, ...data] = readFileSync('./data/방금_그_곡.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const m = data[cur++]
		const n = parseInt(data[cur++])
		const musicInfos = new Array(n).fill(0)
			.map(_ => data[cur++])
		const answer = data[cur++]
		console.log(answer, solve(m, musicInfos))
	}

})()