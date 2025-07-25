
## 실행방법
1. swift 설치
2. swift 테스트 코드 실행  
	```sh
	swift test --filter "[타겟 이름]/[파일 이름]"
	```
	- 타겟 
		| 최상위 폴더명 	| 타겟 이름  |
		| --- 			| --- |
		| cote 			| coteTests |

## 코드 작성 요령
1. 테스트 코드 작성
2. 코드 작성
3. 테스트 코드 통과 하는지 확인 
	```sh
	swift test --filter "coteTests/세_수의_합"
	```
4. swiftlint 점검
	```sh
	swiftlint --fix
	```
5. swiftformat 점검
	```sh
	swiftformat .
	```
