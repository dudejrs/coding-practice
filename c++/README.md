## 실행 방법

1. 각 소스파일 디렉터리로 이동
	```sh
	## cd [project rooot]/c++/[ToSrcDirectory]
	cd ./c++/algorithm
	```
1. 컴파일
	```sh
	## make [소스파일 이름]
	make binaryTree
	```
1. 실행
	```sh
	## ./[소스파일 이름].out
	./binaryTree.out
	```

## 코드 작성 요령 
1. 테스트 코드 작성
2. 코드 작성
3. 포매터 적용 
	- clang-format이 깔려져 있지 않으면 깔아준다. 
	- 다음 명령어를 실행한다. 
		```sh
		clang-format -i **/*.cpp
		```
