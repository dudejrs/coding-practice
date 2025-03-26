#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(int servers, bool sticky, vector<int> requests) {
  vector<vector<int>> answer(servers);
  queue<int> q;
  map<int, int> server;

  for (int request : requests) {
    q.push(request);
  }

  while (!q.empty()) {
    for (int i = 0; i < servers; i++) {
      if (q.empty()) {
        break;
      }

      int r = q.front();
      q.pop();

      if (sticky) {
        if (server.find(r) == end(server)) {
          answer[i].push_back(r);
          server[r] = i;
        } else {
          answer[server[r]].push_back(r);
        }
      } else {
        answer[i].push_back(r);
      }
    }
  }

  return answer;
}