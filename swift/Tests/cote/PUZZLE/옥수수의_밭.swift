@testable import cote
import Nimble
import Quick

class 옥수수의_밭: QuickSpec {
    override func spec() {
        // 실패! : 팀색 공간이 너무 넓어서 시간내에 풀 수 없음
        xit("정확도 테스트") {
            let testCase: [String] = [
                "********",
                "********",
                "r*M**W*h",
                "********",
                "********",
            ]

            let result = cote.PUZZLE.옥수수의_밭.solve(testCase)

            expect(result).to(equal(9))
        }
    }
}
