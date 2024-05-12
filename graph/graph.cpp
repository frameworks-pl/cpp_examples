#include "pch.h"
#include <string>
#include <vector>
#include <queue>

class Node {

    public:
        Node(const std::string& name) {
            visited = false;
            this->name = name;
        }
        
        Node* add(Node* pNode) {
            nodes.push_back(pNode);
            return pNode;
        }
        
        const std::string& getName() {
            return name;
        }
        
        bool getVisited() {
            return this->visited;
        }        
        
        bool hasChildren() {
            return nodes.empty() == false;
        }
        
        void dfsVisit(std::vector<Node*>& vistedNodes) {
        
            //first of all mark myself as visited
            visited = true;
            
            vistedNodes.push_back(this);            
            
            std::vector<Node*>::iterator it;
            for (it = nodes.begin(); it < nodes.end(); it++) {
                if (!(*it)->getVisited()) {
                    (*it)->dfsVisit(vistedNodes);
                }    
            }            
        }
        
        
        void bfsVisit(std::queue<Node*>& nodesToVisit, std::vector<Node*>& visistedNodes) {
        
            visited = true;
            visistedNodes.push_back(this);
            
            std::vector<Node*>::iterator it;
            for (it = nodes.begin(); it < nodes.end(); it++) {
                if (!(*it)->getVisited() && nodesAlreadyInQueue.find(*it) == nodesAlreadyInQueue.end()) {
                    nodesAlreadyInQueue.insert(std::map<Node*, int>::value_type(*it, 1));
                    nodesToVisit.push(*it);
                }
            }
            
            if (!nodesToVisit.empty()) {
                Node* nextNode = nodesToVisit.front();
                nodesToVisit.pop();
                nextNode->bfsVisit(nodesToVisit, visistedNodes);
            }                           
        }
        

    protected:
        static std::map<Node*, int> nodesAlreadyInQueue;
        std::vector<Node*> nodes;
        std::string name;
        bool visited;
        
        std::queue<Node*> nodesQueue;

};

std::map<Node*, int> Node::nodesAlreadyInQueue;

TEST(Graph, rectangleDFS) {

    Node* pLeftBottom = new Node("LeftBottom");
    Node* pRightBottom = pLeftBottom->add(new Node("LeftTop"))->add(new Node("RightTop"))->add(new Node("RightBottom"));
    pRightBottom->add(pLeftBottom);
    
    std::vector<Node*> visited;
    pLeftBottom->dfsVisit(visited);
    
    ASSERT_EQ(4, visited.size());
    ASSERT_EQ("LeftBottom", visited[0]->getName());
    ASSERT_EQ("LeftTop", visited[1]->getName());
    ASSERT_EQ("RightTop", visited[2]->getName());
    ASSERT_EQ("RightBottom", visited[3]->getName());
    
    std::vector<Node*>::iterator it;
    for (it = visited.begin(); it < visited.end(); it++) {
        delete *it;
    }
    visited.clear();
               
}

TEST(Graph, rectangleBFS) {

    Node* pLeftBottom = new Node("LeftBottom");
    Node* pRightBottom = pLeftBottom->add(new Node("RightBottom"));
    Node* pLeftTop = pLeftBottom->add(new Node("LeftTop"));
    Node* pRightTop = pLeftTop->add(new Node("RightTop"));
    pRightBottom->add(pRightTop);
    

    std::vector<Node*> nodesVisited;
    std::queue<Node*> nodesToVisit;
    pLeftBottom->bfsVisit(nodesToVisit, nodesVisited);
    
    ASSERT_EQ(4, nodesVisited.size());
    ASSERT_EQ("LeftBottom", nodesVisited[0]->getName());
    ASSERT_EQ("RightBottom", nodesVisited[1]->getName());
    ASSERT_EQ("LeftTop", nodesVisited[2]->getName());
    ASSERT_EQ("RightTop", nodesVisited[3]->getName());
    
}

TEST(Graph, rectangleWithExtraNodesBFS) {

    Node* pLeftBottom = new Node("LeftBottom");
    Node* pRightBottom = pLeftBottom->add(new Node("RightBottom"));
    Node* pLeftTop = pLeftBottom->add(new Node("LeftTop"));
    Node* pRightTop = pLeftTop->add(new Node("RightTop"));
    pRightBottom->add(pRightTop);
    pLeftBottom->add(new Node("ExtraNode"));
    pLeftBottom->add(new Node("ExtraNode2"));
    
    std::vector<Node*> nodesVisited;
    std::queue<Node*> nodesToVisit;
    pLeftBottom->bfsVisit(nodesToVisit, nodesVisited);
    
    ASSERT_EQ(6, nodesVisited.size());
    ASSERT_EQ("LeftBottom", nodesVisited[0]->getName());
    ASSERT_EQ("RightBottom", nodesVisited[1]->getName());
    ASSERT_EQ("LeftTop", nodesVisited[2]->getName());
    ASSERT_EQ("ExtraNode", nodesVisited[3]->getName());
    ASSERT_EQ("ExtraNode2", nodesVisited[4]->getName()); 
    ASSERT_EQ("RightTop", nodesVisited[5]->getName());        

}