# coding-practice



## 1. c++ 소스파일 실행 방법

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

## 5. go 실행방법

1. 소스파일 디렉토리로 이동 
	```sh
	cd ./go/algorithm
	```


2. 실행 
	1. 소스파일 빌드 후 실행
		- 빌드
			```sh
			go build binaryTree.go
			```
		- 실행 
			```sh
			./binaryTree
			```
	2. 빌드후 실행 
		```sh
		go run binaryTree.go
		```

## 6. kotlin 실행방법 

1. kotlin 디렉토리로 이동 
	```sh
	cd ./kotlin
	```

2. 컴파일
	```sh
	kotlinc -d target -include-runtime algorithm/binaryTree.kt 
	```

3. 실행
	```sh
	kotlin -classpath target com.example.algorithm.BinaryTreeKt
	```




