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


## 2. java 소스파일 실행 방법

1. java 디렉토리로 이동
	```sh
	cd  ./java
	```

2. 실행 방법
	1. 전체 패키지 컴파일 후 실행 
		- jar파일로 전체 패키지 컴파일
			```sh
			mvn package
			```
		- 실행
			```sh
			## java -cp [타겟 jar위치] [실행할 클래스] 
			java -cp target/java-1.0-SNAPSHOT.jar com.example.algorithm.BinaryTree
			```
	2. 단일 소스파일 컴파일 후 실행 
		- 소스파일 컴파일
			```sh
			##a javac -d [컴파일 파일 저장할 디렉토리 위치] [실행할 java파일]
			javac -d target -cp src/main/* src/main/com/example/algorithm/BinaryTree.java
			```
		- 실행
			```sh
			# java -cp [타겟 디렉토리 위치] [실행할 클래스]
			java -cp target com.exmple.algorithm.BinaryTree
			```
	
## 3. javascipt 실행 방법

1. 소스파일 디렉토리로 이동
	```sh
	cd ./javascript/algorithm
	```
2. 실행 
	```sh
	node binaryTree.js
	```

## 4. python 실행 방법
1. 소스파일 디렉토리로 이동
	```sh
	cd ./python/algorithm
	```

2. 실행 
	```sh
	python binaryTree.py
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


