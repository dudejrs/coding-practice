@testable import cote
import Nimble
import Quick

typealias Triplet = cote.LTCD.세_수의_합.Triplet

class 세_수의_합: QuickSpec {
    override func spec() {
        describe("정확도 테스트") {
            let testReturnExpectedSet: (_ items: [Int], _ expected: Set<Triplet>) -> Void = { items, expected in
                it("같은 튜플의 집합을 반환하는지 확인") {
                    let result = cote.LTCD.세_수의_합.solve(items: items)
                    expect(result).to(equal(expected))
                }
            }

            testReturnExpectedSet(
                [-2, -1, 0, 1, 2, 3],
                [Triplet(-2, -1, 3), Triplet(-2, 0, 2), Triplet(-1, 0, 1)]
            )

            testReturnExpectedSet(
                [-4, 0, 1, 2, 3],
                [Triplet(-4, 1, 3)]
            )
            testReturnExpectedSet(
                [0, -1, 2, -3],
                []
            )
            testReturnExpectedSet(
                [0, 0, 0],
                [Triplet(0, 0, 0)]
            )
        }

        describe("결과물의 정합성 테스트") {
            for _ in 0 ... 10 {
                it("세 수의 합이 0인지 테스트") {
                    let items: [Int] = Array((-100 ... 100).shuffled().prefix(100))
                    let result = cote.LTCD.세_수의_합.solve(items: items)

                    expect(result).to(allPass { $0[0] + $0[1] + $0[2] == 0 })
                }
            }
        }
    }
}
