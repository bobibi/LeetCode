/*
 * LeetCodeHelpers.hh
 *
 *  Created on: May 23, 2015
 *      Author: bobibi
 */

#ifndef LEETCODEHELPERS_HH_
#define LEETCODEHELPERS_HH_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <typeinfo>
using namespace std;

template<class T>
ostream& operator << (ostream& out, vector<T> obj) {
	if(obj.size()==0) return out << "[](0)";
	//out << typeid(obj[0]).name() << endl;
	bool nestedVector = (string(typeid(obj[0]).name(), 14) == "NSt3__16vector");
	!nestedVector && out << '[';
	bool first = true;
	const char* deli = nestedVector?"\n":", ";
	for(typename vector<T>::iterator it=obj.begin(); it!=obj.end(); it++) {
		!first && out << deli;
		out << *it;
		first = false;
	}
	!nestedVector && out << "]";
	out << "(" << obj.size() << ")";
	return out;
}

template<class T>
T convert(const string& str, int from, int to) {
	cerr << "Please implement the converter function for " << (typeid(T).name()) << endl;
}

template<>
char convert<char>(const string& str, int from, int to) {
	if(str[from]==',' || str[from]=='[') from++;
	while(from<=to && (str[from]==' '||str[from]=='\t')) from++;

	if(from>to || str[from]==']') return '\0';
	return str[from];
}
template<>
int convert<int>(const string& str, int from, int to) {
	int ans = 0, sign = 1;
	if(str[from]==',' || str[from]=='[') from++;
	while(from<=to && (str[from]==' '||str[from]=='\t')) from++;
	if(str[from]=='-') {
		sign = -1;
		from++;
	}
	if(str[from]=='+') from++;
	while(from<=to) {
		if(str[from]<'0' || str[from]>'9') break;
		ans *= 10;
		ans += str[from]-'0';
		from++;
	}
	return ans*sign;
}

/**
 * ["abc", "de", "eghi", ]
 * OR: [ abc, de     , eghi] (trim prefix and suffix white spaces)
 */
template<>
string convert<string>(const string& str, int from, int to) {
	if(str[from]==',' || str[from]=='[') from++;
	while(from<=to && (str[from]==' '||str[from]=='\t')) from++;
	while(from<=to && (str[to]==' '||str[to]=='\t')) to--;
	//cout << str.substr(from, to-from+1) << endl;
	if(from<=to && str[from]=='"') from++;
	if(to>=from && str[to]=='"') to--;
	if(from>to) return "";
	return str.substr(from, to-from+1);
}

/**
 * "[a,b,,c,,d]"
 */
template<class T>
vector<T> makeVector1(const string& str) {
	//TODO: validation
	vector<T> ans;
	int i;
	for(i=0; i<str.size(); i++) { // seeking array start
		if(str[i]=='[') break;
	}
	i++;
	while(i<str.size() && (str[i]==' '||str[i]=='\t'))i++;
	if(i>=str.size() || str[i]==']') return ans;
	for(;i<str.size(); i++) {
		if(str[i]==']') break; // array end
		if(str[i]==' ' || str[i]=='\t') continue; // skip white space
		int j = i+1;
		while(j<str.size() && str[j]!=',' && str[j]!=']') j++;
		ans.push_back(convert<T>(str, i, j-1));
		i = j-1;
	}
	return ans;
}

/**
 * "[[],[],[]]
 */
template<class T>
vector<vector<T> > makeVector2(const string& str) {
	//TODO: validation
	vector<vector<T> > ans;
	int i;
	for(i=0; i<str.size(); i++) { // seeking array start
		if(str[i]=='[') break;
	}
	for(i++;i<str.size(); i++) {
		while(i<str.size() && str[i]!='[') i++;
		if(i>=str.size()) break;
		int len = 1;
		while(i+len-1<str.size() && str[i+len-1]!=']') len++;
		if(i+len-1>=str.size()) break;
		ans.push_back(makeVector1<T>(str.substr(i,len)));
		i += len;
	}
	return ans;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* makeTree(const string& str) {
	TreeNode* ans;
	vector<string> array = makeVector1<string>(str);
	//cout << array << endl;
	queue<TreeNode**> q;
	q.push(&ans);
	for(vector<string>::iterator it = array.begin(); it != array.end() && q.size(); it++) {
		//cout << "hello" << *it << endl;
		TreeNode** p = q.front(); q.pop();
		if(*it == "#" || *it == "null") {
			*p = NULL;
			continue;
		}
		*p = new TreeNode(convert<int>(*it, 0, it->size()-1));
		//cout << *it << ": (*p)->val=" << (*p)->val << endl;
		q.push(&((*p)->left));
		q.push(&((*p)->right));
	}
	while(q.size()) {
		TreeNode** p = q.front(); q.pop();
		*p = NULL;
	}

	return ans;
}

ostream& operator << (ostream& out, TreeNode* root) {
	//printf("%p\n", root);
	queue<TreeNode*> q1, q2, *p1, *p2;
	p1 = &q1;
	p2 = &q2;
	p1->push(root);
	while(p1->size()) {
		out << "[";
		if(p1->front()) {
			out << p1->front()->val;
			p2->push(p1->front()->left);
			p2->push(p1->front()->right);
		}
		else out << "#";
		p1->pop();
		while(p1->size()) {
			out << ", ";
			if(p1->front()) {
				out << p1->front()->val;
				p2->push(p1->front()->left);
				p2->push(p1->front()->right);
			}
			else out << "#";
			p1->pop();
		}
		out << "]" << endl;
		swap(p1, p2);
	}

	return out;
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* makeList(const string& str) {
	ListNode *ans;
	ListNode **pp = &ans;
	vector<int> values = makeVector1<int>(str);
	for(int i=0; i<values.size(); i++) {
		*pp = new ListNode(values[i]);
		pp = &((*pp)->next);
	}
	*pp = NULL;
	return ans;
}

ostream& operator << (ostream& out, ListNode* head) {
	out << "[";
	if(head) {
		out << head->val;
		head = head->next;
	}
	while(head) {
		out << ", " << head->val;
		head = head->next;
	}
	out << "]";
	return out;
}

#endif /* LEETCODEHELPERS_HH_ */
