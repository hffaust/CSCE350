/*
 *	Harry Faust
 *	CSCE350
 *	Huffman Code
 *	5.1.18
 */ 

#ifndef PROGRAM4_H
#define PROGRAM4_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

typedef struct char_freq{
  char c;
  double freq;

  char_freq(char c, double freq)
	:c(c),
	freq(freq)
	{}
		
} CFreq;

typedef struct char_code{
  char c;
  std::string code;
  char_code(char c, std::string code)
    :c(c),
     code(code)
  {}
} CCode;


struct HuffNode{

	char data;
	double frequency;
	HuffNode *left;
	HuffNode *right;


	HuffNode(char d, double f){
		this->frequency = f;
		this->data = d;
		this->left = nullptr;
		this->right = nullptr; 
	}

	~HuffNode(){
		delete left;
		delete right;
	}


 	class compare{
	public:
          	bool operator()(HuffNode *left, HuffNode *right)
          	{
                   return (left->frequency > right->frequency);
          	}

	};
};//end of HuffNode Struct

void assignHuffCodes(HuffNode *root, std::string str, std::vector<CCode>& charCodeVector){
//	if (!root)
//		return charCodeVector;

	if(root->data != '$')
	{
		charCodeVector.push_back(char_code(root->data, str));
	}
	else{
		assignHuffCodes(root->left,  str + "0", charCodeVector);
        	assignHuffCodes(root->right, str + "1", charCodeVector);
	}
	
};


HuffNode* buildHuffmanTree(std::vector<CFreq> cfs){
	         HuffNode *root = NULL;
         int size = cfs.size();
         std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffNode::compare> minHeap;
         for(int i = 0; i<size; i++) //++i
         {
                 minHeap.push(new HuffNode(cfs[i].c, cfs[i].freq));
         }
         while(minHeap.size() != 1)
         {
                 HuffNode *left, *right;
                 left = minHeap.top();
                 minHeap.pop();
                 right = minHeap.top();
                 minHeap.pop();
         
                 root = new HuffNode('$', left->frequency + right->frequency);
                 root->left = left;
                 root->right = right;
                 minHeap.push(root);
         }
	return minHeap.top();
};


//input: vector of CFreqs 
//returns: vector of CCodes
std::vector<CCode> getHuffCodes(std::vector<CFreq > cfs){
	
	std::vector<CCode> codes;// = new std::vector<CCode>(); // = new std::vector<CCode>();

	HuffNode *HuffTree = buildHuffmanTree(cfs);
	assignHuffCodes(HuffTree,"", codes);
	return codes;
}

#endif //PROGRAM4_H
