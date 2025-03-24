

## 실행 방법
### 1. 테스트 코드가 따로 없는 경우 
1. 빌드 실행 
	```sh
	./gradlew build
	```
2. 컴파일된 코드 실행
	```sh
	kotlin -classpath build/libs/java_coding_test-1.0-SNAPSHOT.jar com.example.algorithm.BinaryTree
	```

### 2. 테스트 코드가 있는 경우 
추가 작성 예정입니다. 

## 코드 작성 요령 
1. 테스트 코드 작성
2. 코드 작성
3. 포매터 적용 
	```sh
	./gradlew spotlessApply
	```
