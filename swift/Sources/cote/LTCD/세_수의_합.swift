import Foundation

public extension cote.LTCD {
    enum 세_수의_합 {
        public struct Triplet: Hashable {
            let value: (Int, Int, Int)

            public init(_ a: Int, _ b: Int, _ c: Int) {
                value = (a, b, c)
            }

            public func hash(into hasher: inout Hasher) {
                hasher.combine(value.0)
                hasher.combine(value.1)
                hasher.combine(value.2)
            }

            public static func == (lhs: Triplet, rhs: Triplet) -> Bool {
                return lhs.value == rhs.value
            }

            subscript(index: Int) -> Int {
                switch index {
                case 0: return value.0
                case 1: return value.1
                case 2: return value.2
                default:
                    fatalError("Index out of Range")
                }
            }
        }

        static func search(items: [Int], startIndex i: Int) -> Set<Triplet> {
            var left = i + 1, right = items.count - 1
            var result = Set<Triplet>()

            while left < right {
                let sum = items[i] + items[left] + items[right]

                if sum < 0 {
                    left += 1
                } else if sum > 0 {
                    right -= 1
                } else {
                    result.insert(Triplet(items[i], items[left], items[right]))

                    while left < right && items[left] == items[left + 1] {
                        left += 1
                    }
                    while left < right && items[right] == items[right - 1] {
                        right -= 1
                    }

                    left += 1
                    right -= 1
                }
            }

            return result
        }

        public static func solve(items rawItems: [Int]) -> Set<Triplet> {
            let items = rawItems.sorted()
            let n = items.count
            var result = Set<Triplet>()

            for (i, num) in items.prefix(n - 2).enumerated() {
                if num > 0 {
                    break
                }

                if i > 0 && items[i] == items[i - 1] {
                    continue
                }

                result = result.union(search(items: items, startIndex: i))
            }

            return result
        }
    }
}
