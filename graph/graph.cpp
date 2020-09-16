#include <../include/gtest/gtest.h>
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
            
            std::vector<Node*>::iterator it;
            for (it = nodes.begin(); it < nodes.end(); it++) {
                if (!(*it)->getVisited()) {
                    (*it)->dfsVisit(vistedNodes);
                }    
            }
            
            //if there are no more nodes to visit, add myself to visited
            vistedNodes.push_back(this);

        }
        
        
        void bfsVisist(std::queue<Node*> nodesToVisit) {
        
            visited = true;
            
            std::vector<Node*>::iterator it;
            for (it = nodes.begin(); it > nodes.end(); it++) {
                if (!(*it)->getVisited()) {
                nodesToVisit.push(*it);
                }
            }
            
            if (!nodesToVisit.empty()) {
                Node* nextNode = nodesToVisit.pop();
                nextNode->bfsVisit(nodesToVisit);
            }                           
        }
        

    protected:
        std::vector<Node*> nodes;
        std::string name;
        bool visited;
        
        std::queue<Node*> nodesQueue;

};

TEST(Graph, rectangleDFS) {

    Node* pLeftBottom = new Node("LeftBottom");
    Node* pRightBottom = pLeftBottom->add(new Node("LeftTop"))->add(new Node("RightTop"))->add(new Node("RightBottom"));
    pRightBottom->add(pLeftBottom);
    
    std::vector<Node*> visited;
    pLeftBottom->dfsVisit(visited);
    
    ASSERT_EQ(4, visited.size());
    ASSERT_EQ("RightBottom", visited[0]->getName());
    ASSERT_EQ("RightTop", visited[1]->getName());
    ASSERT_EQ("LeftTop", visited[2]->getName());
    ASSERT_EQ("LeftBottom", visited[3]->getName());
    
    std::vector<Node*>::iterator it;
    for (it = visited.begin(); it < visited.end(); it++) {
        delete *it;
    }
    visited.clear();
               
}

// TEST(Graph, rectangleBFS) {
// 
//     Node* pLeftBottom = new Node("LeftBottom");
//     Node* pLeftTop = pLeftBottom->add(new Node("RightBottom"))->add(new Node("RightTop"))->add(new Node("LeftTop"));
//     pLeftTop->add(pLeftBottom);
//     
//     std::vector<Node*> visited;
//     pLeftTop->bfsVisit(visited);
//     
//     ASSERT_EQ(    
//     
//}