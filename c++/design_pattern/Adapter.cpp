#include <iostream>
#include <vector>
#include <map>
#include <initializer_list>
#include <boost/functional/hash.hpp>

using namespace std;

struct Point {
	int x, y;
};

struct Line {
	Point start, end;
};

struct VectorObject {
	virtual vector<Line>::iterator begin() = 0;
	virtual vector<Line>::iterator end() =0;
};

struct VectorRectangle : VectorObject {	


	VectorRectangle(int x, int y, int width, int height){
		lines.push_back(Line{Point{x,y}, Point{x+width, y}});
		lines.push_back(Line{Point{x,y}, Point{x, y+height}});
		lines.push_back(Line{Point{x+width,y}, Point{x+width, y+height}});
		lines.push_back(Line{Point{x,y+height}, Point{x+width, y+height}});
	}


	vector<Line>::iterator begin() override{
		return ::begin(lines);
	};

	vector<Line>::iterator end() override{
		return ::end(lines);
	};

	
	private :
		vector<Line> lines;
};


void drawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end){

	for(auto it = start; it != end ; it++){
		cout <<"("<< it->x << ","  << it->y <<")" << " ";
	}
	cout << endl;

	return ;
};

vector<Point> RectToPoints(VectorRectangle obj){
	vector<Point> points;

	for(auto& line : obj){

		int left = min(line.start.x, line.end.x);
		int right = max(line.start.x, line.end.x);
		int top = min(line.start.y, line.end.y);
		int bottom = max(line.start.y, line.end.y);

		int dx = right-left;
		int dy = line.end.y - line.start.y;


		// 수직 수평인 선분들만 다룸
		if( dx == 0 ){
			for(int y = top; y <= bottom; ++y){
				points.emplace_back(Point{left,y});
			}
		} else if (dy == 0){
			for(int x =left; x <= right; ++x){
				points.emplace_back(Point{x, top});
			}
		}
	}
	return points;
}


/*
1. 객체 어댑터
*/

namespace ObjectApdater{
	using namespace std;

	struct LegacyRenderer {
		
		void drawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end){
			return ::drawPoints(start, end);
		}
	};

	struct ClientRenderer{
		virtual void draw(VectorRectangle obj) = 0;
	};

	struct RendererAdapter : ClientRenderer{

		LegacyRenderer lg;

		vector<Point> linesToPoints(VectorRectangle obj){
			return RectToPoints(obj);
		}

		void draw(VectorRectangle obj) override {
			vector<Point> lpo = linesToPoints(obj);
			lg.drawPoints(begin(lpo), end(lpo));
		}
	};


	void main(){
		VectorRectangle rect1(10,10,5,5);
		RendererAdapter ra;
		ra.draw(rect1);
		cout << endl ;
	}

};


/*
2. 클래스 어댑터
*/


namespace ClassAdapter {

	using namespace std;

	struct LegacyRenderer{
		void drawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end){
			return ::drawPoints(start, end);
		}
	};

	struct ClientRenderer{
		void draw(VectorRectangle obj){
			return;
		}
	};

	struct RendererAdapter : LegacyRenderer, ClientRenderer {

		vector<Point> linesToPoints(VectorRectangle obj){
			return RectToPoints(obj);
		}

		void draw(VectorRectangle obj){
			vector<Point> lpo = linesToPoints(obj);
			drawPoints(begin(lpo), end(lpo));
		}
	};	

	void main(){
		VectorRectangle rect1(0,0,5,5); 
		RendererAdapter adapter;
		ClientRenderer rd  = adapter;
		//  rd.draw(rect1); # 원래 이런 의도인듯
		adapter.draw(rect1);
		cout << endl;

	}
};



/*
3. 캐싱 어댑터
*/

namespace CachingAdapter {



	struct Point {
		int x,y;

		friend std::size_t hash_value(const Point& obj){
			std::size_t seed = 0x725C686F;
			boost::hash_combine(seed,obj.x);
			boost::hash_combine(seed,obj.y);
			return seed;
		}
	};

	struct Line{

		Point start, end;
		friend std::size_t hash_value(const Line& obj){
			std::size_t seed = 0x719E6B16;
			boost::hash_combine(seed,obj.start);
			boost::hash_combine(seed,obj.end);
			return seed;
		}
	};


	struct VectorObject {
		virtual vector<Line>::iterator begin() = 0;
		virtual vector<Line>::iterator end() =0;
	};

	struct VectorRectangle : VectorObject {


		VectorRectangle(int x, int y, int width, int height){
			lines.push_back(Line{Point{x,y}, Point{x+width, y}});
			lines.push_back(Line{Point{x,y}, Point{x, y+height}});
			lines.push_back(Line{Point{x+width,y}, Point{x+width, y+height}});
			lines.push_back(Line{Point{x,y+height}, Point{x+width, y+height}});
		}


		vector<Line>::iterator begin() override{
			return ::begin(lines);
		};

		vector<Line>::iterator end() override{
			return ::end(lines);
		};

		
		private :
			vector<Line> lines;
	};

	
	static map<size_t,vector<Point>> cache;

	struct LineToPointAdapter{
		typedef vector<Point> Points;

		LineToPointAdapter(Line line){
			// static map<size_t,vector<Point>> cache;			
			static boost::hash<Line> hash;

			line_hash = hash(line);

			if(cache.find(line_hash) != cache.end())
				return;

			cout << "."<< endl;
			int left = min(line.start.x, line.end.x);
			int right = max(line.start.x, line.end.x);
			int top = min(line.start.y, line.end.y);
			int bottom = max(line.start.y, line.end.y);

			int dx = right-left;
			int dy = line.end.y - line.start.y;


			// 수직 수평인 선분들만 다룸
			Points points;
			if( dx == 0 ){
				for(int y = top; y <= bottom; ++y){
					points.emplace_back(Point{left,y});
				}
			} else if (dy == 0){
				for(int x =left; x <= right; ++x){
					points.emplace_back(Point{x, top});
				}
			}

			cache[line_hash] = points;
		}

		
		Points::iterator begin() {return cache[line_hash].begin();}
		Points::iterator end() {return cache[line_hash].end();}

		private :
			size_t line_hash;
	};


	void drawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end){

		for(auto it = start; it != end ; it++){
			cout <<"("<< it->x << ","  << it->y <<")" << " ";
		}
		cout << endl;

		return ;
	};

	vector<shared_ptr<VectorObject>> vectorObjects{
		make_shared<VectorRectangle>(10,10,5,5),
		make_shared<VectorRectangle>(10,10,5,5)
	};


	void main(){
		vector<Point> points;

		for(auto& o : vectorObjects){
			for(auto& l : *o){

				LineToPointAdapter lpo(l);
				for(auto& p : lpo){
					points.push_back(p);
				}
			}
		}

		drawPoints(std::begin(points), std::end(points));
	}
}


int main(void){

	ObjectApdater::main();	
	ClassAdapter::main();
	CachingAdapter::main();

	return 0;
}