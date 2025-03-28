## 실행 방법 

1. poetry 설치 
2. poetry 의존성 패키지 설치
	```
	poetry install --no-root
	```
3. poetry 가상환경 실행
	```
	poetry env activate
	```
4. 해당 파일 실행 
	1. 테스트 파일이 있는 경우 : 테스트 실행 
		```sh
		python -m pytest [테스트파일]
		```
	2. 테스트 파일이 없는 경우 : 직접 소스파일 실행
		```sh
		python [테스트파일]
		```

추가 작성 예정입니다. 

## 코드 작성 요령 
1. 테스트 코드 작성
2. 코드 작성
3. mypy 타이핑 점검
	```sh
	mypy [작성한 파일]
	```
4. Black 점검
	```sh
	black [작성한 파일]
	```
5. 테스트 코드 실행
	```sh
	pytest [실행할 파일]
	``` 