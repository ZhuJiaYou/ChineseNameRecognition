using namespace std;

//判断该行数据是否属于测试集，用于交叉验证
//total为(训练集+测试集)总行数，lineNum为判断行，fold为fold折交叉验证，no为第no次交叉验证
bool judgeTest(int total, int lineNum, int fold, int no)
{
    int testSize = total / fold;
    if((lineNum > testSize * (no - 1)) && (lineNum <= testSize * no))
        return true;
    else
        return false;
}

//从作业二的语料前10000行中获取8:2的训练集和测试集
//origin、dest1和dest2、分别为原始语料、训练集和测试集，fold为fold折交叉验证
void basicFileProcess(const string &origin, const string &dest1, const string &dest2, const int fold)
{
	ifstream input(origin);
	ofstream output1(dest1, ofstream::app);
	ofstream output2(dest2, ofstream::app);

    string line;
    for(int i = 0; i < 10000; ++i)
    {
    	getline(input, line);
    	if(judgeTest(10000, i + 1, fold, 2))  //**注意根据1~fold修改no**
    	{
    	    output2 << line;
    		output2 << endl;
    	}
    	else
    	{
    		output1 << line;
    		output1 << endl;
    	}
    }
}

//处理C++中文字符串分割为字符乱码问题
void splitChinese(const string &word, vector<string> &characters)
{
    int num = word.size();
	int i = 0;
	while(i < num)
	{
	    int size;    
	    if(word[i] & 0x80)
	    {
	        if(word[i] & 0x20)
	        {
	            if(word[i] & 0x10)
	            {
	                if(word[i] & 0x08)
	                {
	                    if(word[i] & 0x04)
	                    {
	                         size = 6;
	                    }
	                    else
	                    {
	                        size = 5;
	                    }
	                }
	                else
	                {
	                    size = 4;
	                }
	            }
	            else
	            {
	                size = 3;
	            }
	        }
	        else
	        {
	            size = 2;
	        }
	    }
	    else
	    {
	        size = 1;
	    }
	    string subWord;
	    subWord = word.substr(i, size);
	    characters.push_back(subWord);
        i += size;
     }
}

//将语料处理为CRF++标准格式
void format(const string &origin, const string &dest)
{
    ifstream input(origin);
    ofstream output(dest, ofstream::app);
    
    string lineStr, word;
    while(getline(input, lineStr))
    {
        istringstream line(lineStr);

        while(line >> word)
        {
            auto pos = word.find("/");
            string phrase = word.substr(0, pos);
            string character = word.substr(pos + 1, word.size() - (pos + 1));
            vector<string> charactersOfChinese;
            splitChinese(phrase, charactersOfChinese);
            if(charactersOfChinese.size() == 1)
            {
                output << charactersOfChinese[0] << " " << "S" << " " << character << " ";
                if(character == "nr")
                    output << "B-P" << endl;
                else
                    output << "O" << endl;
            }
            else
            {
                for(int i = 0; i < charactersOfChinese.size(); ++i)
                {
                    if(i == 0)
                    {
                        output << charactersOfChinese[i] << " " << "B" << " " << character << " ";
                        if(character == "nr")
                            output << "B-P" << endl;
                        else
                            output << "O" << endl;
                    }
                    else if(i == (charactersOfChinese.size() - 1))
                    {
                        output << charactersOfChinese[i] << " " << "E" << " " << character << " ";
                        if(character == "nr")
                            output << "I-P" << endl;
                        else
                            output << "O" << endl;
                    }
                    else
                    {
                        output << charactersOfChinese[i] << " " << "M" << " " << character << " ";
                        if(character == "nr")
                            output << "I-P" << endl;
                        else
                            output << "O" << endl;
                    }
                }
            }
        }
    }
}

//根据标注结果文件计算准确率、召回率以及F-score
void calculate(const string &output)
{
    double precision;
    double recall;
    double f1;
    int tp = 0;  //预测为人名且原标注为人名数
    int p = 0;  //预测为人名数
    int t = 0;  //测试集实际含人名标注数
    
    ifstream input(output);
    string lineStr, word;
    while(getline(input, lineStr))
    {
        istringstream line(lineStr);

        vector<string> info;
        while(line >> word)
        {
            info.push_back(word);
        }
        if(info.size() == 5)
        {
            if((info[4] == "B-P") || (info[4] == "I-P"))
            {
                ++p;
                if(info[3] == info[4])
                {
                    ++tp;
                }
            }
            
            if((info[3] == "B-P") || (info[3] == "I-P") )
            {
                ++t;
            }
        }
        
    }
    
    precision =  tp * 1.0 / p;
    recall = tp * 1.0 / t;
    f1 = 2 * precision * recall / (precision + recall);
    
    cout << "precision = " << precision << endl;
    cout << "recall = " << recall << endl;
    cout << "F-score = " << f1 << endl;
    
    cout << "人名正确预测数：" << tp << endl;
    cout << "预测为人名数：" << p << endl;
    cout << "测试集实际标注为人名数：" << t << endl;
}