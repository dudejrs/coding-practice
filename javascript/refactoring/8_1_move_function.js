

/* trackSummary 함수 안에 있는 중첩함수 calculateDistance를 최상위 스코프로 옮겨라 
 */


function trackSummary(points){
	const totalTime = caculateTime();
	const totalDistance =top_calculateDistance(points);
	const pace = totalTime / 60 / totalDistance;
	return {
		time : totalTime,
		distnae : totalDistance,
		pace : pace
	};

	// function calculateDistance() {
	// 	return top_calculateDistance(points)
	// }

	function caculateTime(){
		// ...
		return 0.001;
	}
};


function top_calculateDistance(points) {
	let result = 0;
	for( let i =1; i <points.length; i++){
		result += distance(points[i-1], points[i]);
	}
	
	// function distance(p1, p2){
	// 	// ...
	// 	return 1;
	// }

	return result;
}

function distance(p1, p2){
		// ...
		return 1;
}


points = [[0,1],[0,2]]
console.log(trackSummary(points))