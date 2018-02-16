#ifndef AA_SIPP_H
#define AA_SIPP_H

#include "cSearch.h"
#include "constraints.h"
#include <random>
#include <algorithm>
class AA_SIPP : public cSearch
{

public:

    AA_SIPP(double weight, int constraints_type, int rescheduling, int timelimit, int prioritization, int startsafeinterval);
    ~AA_SIPP();
    SearchResult startSearch(cLogger *Log, cMap &Map);

private:

    void addOpen(Node &newNode);
    Node findMin(int size);
    bool stopCriterion();
    double calculateDistanceFromCellToCell(double start_i, double start_j, double fin_i, double fin_j);
    bool lineOfSight(int i1, int j1, int i2, int j2, const cMap &map);
    void findSuccessors(const Node curNode, const cMap &Map, std::list<Node> &succs, int numOfCurAgent);
    void makePrimaryPath(Node curNode);
    void makeSecondaryPath(Node curNode);
    void calculateLineSegment(std::vector<Node> &line, const Node &start, const Node &goal);
    void addConstraints(){}
    Node resetParent(Node current, Node Parent, const cMap &Map);
    bool findPath(int numOfCurAgent, const cMap &Map);
    std::vector<conflict> CheckConflicts();//bruteforce checker. It splits final(already built) trajectories into sequences of points and checks distances between them
    void setPriorities(const cMap& Map);
    bool changePriorities(int bad_i);
    double weight;
    bool breakingties;
    int rescheduling;
    int constraints_type;
    int timelimit;
    int prioritization;
    int startsafeinterval;
    unsigned int closeSize, openSize;
    std::list<Node> lppath;
    std::vector<std::list<Node>> open;
    std::unordered_multimap<int, Node> close;
    std::vector<Node> hppath;
    std::vector<std::vector<int>> priorities;
    std::vector<int> current_priorities;



    Constraints *constraints;
};

#endif // AA_SIPP_H
