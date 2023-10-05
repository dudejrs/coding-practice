/* 
변수 이름 cpytpHD로 바꾸는 데, 
변수가 폭 넓게 쓰기때문에  캡슐화를 진행한 뒤 이름을 바꾸려고 한다.
*/

// 바꿀 변수
let cpytpHD = "untitled";
// let tpHD = cpytpHD;

function title(){return cpytpHD;}
function setTitle(arg){cpytpHD = arg;}


// 변수를 활용하는 코드들 
result = ' ... ';
obj = { articleTitle : 'someTitle'}
result += `<h1>${title()}</h1>`;
setTitle(obj['articleTitle']);