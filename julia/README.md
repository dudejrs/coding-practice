# julia

## 실행 방법 

### 1. 테스트 코드가 있는 경우 

1. 줄리아 Repl 실행
	```sh
	julia
	```
2. 현재 프로젝트 환경 설정  
	```julia
	using Pkg
	Pkg.activate(".")
	```
3. 테스트실행 
	```julia
	Pkg.test()
	```

## 코드 작성 요령 

1. 테스트 코드 작성
2. 코드 작성

3. julia Repl에서 포매터 실행
	```julia
	using JuliaFormatter
	using Glob

	format.(glob("**/*.jl", "src"))
	```
