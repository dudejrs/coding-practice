#include <string>
#include <vector>

using namespace std;

long long solution(long long orderAmount, long long taxFreeAmount,
                   long long serviceFee) {
  // orderAmount : 주문금액
  // taxFreeAmount : 비과세금액
  // serviceFee : 봉사료
  long long answer = orderAmount - serviceFee;
  return answer;
}