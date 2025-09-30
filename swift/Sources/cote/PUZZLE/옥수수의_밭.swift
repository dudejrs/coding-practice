import Collections

public extension cote.PUZZLE {
    enum 옥수수의_밭 {
        enum Chicken {
            case rooster, hen
        }

        struct Displacement {
            let dy: Int
            let dx: Int
        }

        enum Direction: CaseIterable {
            case left, right, up, down

            var delta: Displacement {
                switch self {
                case .left: return Displacement(dy: 0, dx: -1)
                case .right: return Displacement(dy: 0, dx: 1)
                case .up: return Displacement(dy: -1, dx: 0)
                case .down: return Displacement(dy: 1, dx: 0)
                }
            }
        }

        struct Position: Hashable {
            let y: Int
            let x: Int

            func move(_ direction: Direction) -> Position {
                let d = direction.delta

                return Position(y: y + d.dy, x: x + d.dx)
            }

            func inBoundary(height: Int, width: Int) -> Bool {
                return (0 ..< height) ~= y && (0 ..< width) ~= x
            }

            func getEscapePosition(from others: [Position]) -> [Position] {
                let allCases = next()
                let maxDistance = allCases.map { $0.minDistance(from: others) }.max()
                return Array(allCases.filter {
                    $0.minDistance(from: others) == maxDistance
                }.prefix(1))
            }

            func next() -> [Position] {
                return Direction.allCases.map {
                    self.move($0)
                }
            }

            func minDistance(from others: [Position]) -> Int {
                return others.map {
                    $0.distance(from: self)
                }.min() ?? 0
            }

            func distance(from other: Position) -> Int {
                return abs(other.y - y) + abs(other.x - x)
            }
        }

        struct State: Hashable {
            let man: Position
            let woman: Position
            let rooster: Position
            let hen: Position
            let height, width: Int
            let count: UInt
            let caughted: Set<Chicken>

            var completed: Bool {
                return caughted.contains(.hen) && caughted.contains(.rooster)
            }

            func hash(into hasher: inout Hasher) {
                hasher.combine(man)
                hasher.combine(woman)
                hasher.combine(rooster)
                hasher.combine(hen)
            }

            static func == (lhs: State, rhs: State) -> Bool {
                return lhs.man == rhs.man
                    && lhs.woman == rhs.woman
                    && lhs.rooster == rhs.rooster
                    && lhs.hen == rhs.hen
            }

            func next() -> [State] {
                var nextStates: [State] = []

                for (newMan, newWoman) in product(man.next(), woman.next()) {
                    var newCaughted = caughted

                    if !newMan.inBoundary(height: height, width: width)
                        || !newWoman.inBoundary(height: height, width: width)
                    {
                        continue
                    }

                    if !newCaughted.contains(.rooster)
                        && newMan == rooster || newWoman == rooster
                    {
                        newCaughted.insert(.rooster)
                    }

                    if !newCaughted.contains(.hen)
                        && newMan == hen || newWoman == hen
                    {
                        newCaughted.insert(.hen)
                    }

                    var newRoosters: [Position] = [rooster]
                    var newHens: [Position] = [hen]

                    if !newCaughted.contains(.rooster) {
                        newRoosters = rooster.getEscapePosition(from: [newMan, newWoman])
                    }

                    if !newCaughted.contains(.hen) {
                        newHens = hen.getEscapePosition(from: [newMan, newWoman])
                    }

                    for (newRooster, newHen) in product(newRoosters, newHens) {
                        nextStates.append(
                            State(man: newMan, woman: newWoman, rooster: newRooster, hen: newHen,
                                  height: height, width: width, count: count + 1, caughted: newCaughted)
                        )
                    }
                }

                return nextStates
            }
        }

        static func product<S1: Sequence, S2: Sequence>(_ s1: S1, _ s2: S2) -> [(S1.Element, S2.Element)] {
            var result: [(S1.Element, S2.Element)] = []

            for a in s1 {
                for b in s2 {
                    result.append((a, b))
                }
            }

            return result
        }

        static func getInitalState(_ map: [String]) -> State {
            let height = map.count
            let width = map[0].count

            var man = Position(y: 0, x: 0)
            var woman = Position(y: 0, x: 0)
            var rooster = Position(y: 0, x: 0)
            var hen = Position(y: 0, x: 0)

            for (i, row) in map.enumerated() {
                for (j, char) in row.enumerated() {
                    switch char {
                    case "r":
                        rooster = Position(y: i, x: j)
                    case "h":
                        hen = Position(y: i, x: j)
                    case "M":
                        man = Position(y: i, x: j)
                    case "W":
                        woman = Position(y: i, x: j)
                    case _:
                        continue
                    }
                }
            }

            return State(man: man, woman: woman, rooster: rooster, hen: hen,
                         height: height, width: width, count: 0, caughted: [])
        }

        public static func solve(_ map: [String]) -> UInt {
            var count: UInt = 0

            var queue = Deque<State>()
            var visited: Set<State> = []

            let initialState = getInitalState(map)

            queue.append(initialState)

            while !queue.isEmpty {
                let cur: State! = queue.popFirst()
                visited.insert(cur)

                if cur.completed {
                    count = cur.count
                    break
                }

                let nextStates = cur.next().filter {
                    !visited.contains($0)
                }
                queue.append(contentsOf: nextStates)
            }

            return count
        }
    }
}
