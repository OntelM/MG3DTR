#include "stdafx.h"
#include "parser.h"

Parser::Parser(){
	
	
}
string delims(""); //;,:. \n\t
void Parser::convertObject(string file) {
	GLfloat a = 0.04f;
	GLfloat b = 0.03f;
	GLfloat c = 0.05f;
	


	//pos[1].x = a; pos[1].y = b; pos[1].z = c;

	string line;
	int i = 0;
	ifstream myfile(file);
	vector<string> linii;
	

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			
			wordVector.clear();
			delims.clear();
			if (i == 0) {
				
				delims.append(":");
				test(line);
				string var1 = wordVector[0];
				int nrVer = stoi(wordVector[1]);
				setNrVer(nrVer);
				wordVector.clear();
				string asad = "asd";
			}
			else if (i > 0 && i <= nrVer) {
				delims.append("[]");
				test(line);
				string pozitie = wordVector[1];
				string normal = wordVector[3];
				string binom = wordVector[5];
				string tgt = wordVector[7];
				string uv = wordVector[9];
				wordVector.clear();
				delims.append(",");
				test(pozitie);
				float f1 = stof(wordVector[0]);
				float f2 = stof(wordVector[1]);
				float f3 = stof(wordVector[2]);

				// add vertex ------------------------------------------------
				Vertex asd;
				asd.pos.x = f1; asd.pos.y = f2; asd.pos.z = f3;
				asd.color.x = 1.0f; asd.color.y = 1.0f; asd.color.z = 1.0f;
				verList[i - 1] = asd;

				string asad = "asd";
				
			}
			else if (i == nrVer+1) {
				delims.append(":");
				test(line);
				string var1 = wordVector[0];
				int nrInd = stoi(wordVector[1]);
				setNrInd(nrInd);
				wordVector.clear();
				string asad = "asd";
			}
			else if (i > nrVer) {
				delims.append(".");
				test(line);
				int var1 = stoi(wordVector[0]);
				string var2 = wordVector[1];
				wordVector.clear();
				delims.clear();
				delims.append(",");
				test(var2);
				int g = var1 * 3;			// rand * 3 indecsi
				int mg = (var1 * 3) + 3;	// (rand * 3 indecsi) + 3
				int j = 0;
				for (g; g < mg; g++) {
					//indices[g] = stoi(wordVector[j]);
					indices[g] = stoi(wordVector[j]);
					j = j + 1;
					}
				string asad = "asd";
			}

			
			
			i = i + 1;
			
		}
		myfile.close();
	}
	ddd = verList[nrVer - 1];
	iii = indices[nrInd - 1];
	int iss = 3;
}


void Parser::test(string s) {
	stringstream stringStream(s);
	string word; char c;

	while (stringStream) {
		word.clear();

		// Read word
		while (!isDelim((c = stringStream.get())) && c !=-1)
			word.push_back(c);
		if (c != EOF)
			stringStream.unget();

		wordVector.push_back(word);

		// Read delims
		while (isDelim((c = stringStream.get())));
		if (c != EOF)
			stringStream.unget();
	}
}


	inline bool Parser::isDelim(char c) {
		for (int i = 0; i < delims.size(); i++)
			if (delims[i] == c) {
				return true;
			}
		return false;
	}

	void Parser::setNrVer(int a) {
		nrVer = a;
	}
	int Parser::getNrVer() {
		return nrVer;
	}
	void Parser::setNrInd(int a) {
		nrInd = a;
	}
	int Parser::getNrInd() {
		return nrInd;
	}


