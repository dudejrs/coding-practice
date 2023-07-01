#include <iostream>
#include <string>

using namespace std;


namespace Facade1{

	struct File {
		public :
			File(const string& name) : name(name){}
			string format; 
			
			void write(const string& buffer){
			}
			void save(){
			}

		protected :
			string name;
	};

	struct VideoFile : File{
		VideoFile(const string& name) : File(name){}
	};

	struct Codec {
	};
	struct MPEG4Codec : Codec{
	};
	struct OGGCodec : Codec{
	};

	struct CodecFactory {
		static Codec extract(File file){
			if (file.format == "mp4") 
				return MPEG4Codec();
			else
				return OGGCodec();
		}
		static Codec get(const string& format){
			if (format == "mp4") 
				return MPEG4Codec();
			else
				return OGGCodec();
		}
	};

	struct BitrateReader {
		static string read(File file, Codec codec){
			return "";
		}
		static string convert(string buffer, Codec codec){
			return "";
		}
	};

	struct VideoConverter {

		File convert(const string& filename, const string& format){
			VideoFile file(filename);

			Codec srcCodec = CodecFactory::extract(file);
			Codec dstCodec = CodecFactory::get(format);

			string buffer = BitrateReader::read(file, srcCodec);
			string result = BitrateReader::convert(buffer, dstCodec);
			file.write(result);

			return file;
		}

	};

	void main() {

		VideoConverter converter;
		File file = converter.convert("test.ogg","mp4");
		file.save();

	}	

};


int main(void){

	Facade1::main();

	return 0;
}