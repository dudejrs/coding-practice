from __future__ import annotations
from typing import Generic, TypeVar
import random

T = TypeVar("T")
class MyQueue(Generic[T]) :
	
	def __init__(self) :
		self.input = []
		self.output = []

	def push(self, value: T) :
		self.input.append(value)

	def pop(self) -> T:
		self.peek()
		return self.output.pop()

	def peek(self) -> T:
		if not self.output :
			while self.input :
				self.output.append(self.input.pop())
		return self.output[-1]

	def empty(self) -> bool:
		return len(self.input) == 0 and len(self.output) == 0


if __name__ == "__main__" :

	queue = MyQueue[int]()
	ret = []
	for _ in range(10) :
		t = random.randrange(100)
		queue.push(t)
		ret.append(t)

	print(ret)
	print([ queue.pop() for _ in range(10)])

	pass