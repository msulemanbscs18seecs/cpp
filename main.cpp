#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

std::string parse(std::string str){
		str = ReplaceAll(str, std::string(" "), std::string("%20"));
	return str;
}
int main(){
//FILES
	std::string urlFile = "urlFile.txt";
	std::string titleFile = "titleFile.txt";
	std::string file = "output.txt";

//SETTING UP COMMANDS
	std::string playlistUrl = "https://www.youtube.com/playlist?list=PL6LdaanzFU_X9wAFwOeshpEkzid0Rgwm8";
	std::string format = "-f best";
	std::string urlStr = "youtube-dl "+format+" --get-url "+playlistUrl+" > "+urlFile;
	std::string titleStr = "youtube-dl --get-title "+playlistUrl+" > "+titleFile;

	const char* urlCommand = urlStr.c_str();
	const char* titleCommand = titleStr.c_str();

//PASSING THE COMMANDS
	//system(urlCommand);
	//system(titleCommand);
//SETTING FILE
	std::string urlLine;
	std::string titleLine;
	
	std::ofstream fileofObject(file);
	std::ifstream urlifObject(urlFile);
	std::ifstream titleifObject(titleFile);

//WRITING TO FILE
	if (titleifObject.is_open()){		
		int counter = 0;
		while ( std::getline(titleifObject, titleLine) && std::getline(urlifObject, urlLine) ){
			std::string str;
			counter++;
			str += "&title="+std::to_string(counter)+"."+parse(titleLine);
			fileofObject << urlLine <<  str << "\n";
		}
		
		titleifObject.close();
		urlifObject.close();
	}
  	else std::cout << "Unable to open urlFile";	


	fileofObject.close();
	return 0;
}