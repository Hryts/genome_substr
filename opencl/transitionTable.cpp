//
// Created by hryts on 6/15/20.
//

#include <string>
#include "transitionTable.h"
//#include "patterns_trie.h"

void updateTrie(std::vector<Node>& trie, const std::string& word, size_t id);

std::string subVectorToStr(std::vector<char> vec, size_t from, size_t to) {
    std::vector<char> subVector(vec.begin()+from, vec.begin()+to);
    std::string strRes(subVector.begin(), subVector.end());
    return strRes;
}

std::vector<Node> markersToTrie(std::vector<char> markers) {
    std::vector<Node> res;

    size_t coma = 0;
    size_t eol = 0;
    int id=10;


    for (size_t i=0;i<markers.size();++i){
        if(markers[i]==',') {
            coma=i;
            id = std::stoi(subVectorToStr(markers, eol, coma));
        }
        if(markers[i]=='\n') {
            eol=i;
            auto marker = subVectorToStr(markers, coma+1, eol);
            updateTrie(res, marker, id);
        }
    }
    return res;
}

std::vector<std::vector<char>> trieToVec(std::vector<Node> trie) {
    std::vector<char> chars;
    std::vector<char> ids;
    std::vector<char> firsts;
    std::vector<char> seconds;
    std::vector<char> thirds;
    std::vector<char> fourths;
    for (auto node:trie){
        chars.push_back(node.ch);
        ids.push_back(node.id);
        firsts.push_back(node.children[0]);
        seconds.push_back(node.children[1]);
        thirds.push_back(node.children[2]);
        fourths.push_back(node.children[3]);
    }
    std::vector<std::vector<char>> res;
    res.push_back(chars);
    res.push_back(ids);
    res.push_back(firsts);
    res.push_back(seconds);
    res.push_back(thirds);
    res.push_back(fourths);

    return res;
}

void updateTrie(std::vector<Node>& trie, const std::string& word, size_t id) {

    if (trie.empty()) {
        Node root{};
        root.ch='!';
        root.id=-1;
        trie.push_back(root);
    }

    Node *previousNodePointer = &trie[0];
    int child_tmp;

    for (int i = 0; i < word.size();++i){
        int child;
        char letter = word[i];

        if (letter == 'A') {
            child = 0;
        }
        else if (letter == 'C') {
            child = 1;
        }
        else if (letter == 'T') {
            child = 2;
        }
        else {
            child = 3;
        }

        Node currentNode{};
        currentNode.id=-1;
        currentNode.ch=i;

        if (i == word.size()-1) {
            currentNode.id = id;
        }
        if (previousNodePointer->children[child] == 0) {
            previousNodePointer->children[child] = trie.size();
            trie.push_back(currentNode);
            previousNodePointer = &currentNode;
        }
        else {
            previousNodePointer = &trie[previousNodePointer->children[child]];
        }
    }
}