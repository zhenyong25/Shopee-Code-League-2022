#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define INF 2147483647
using namespace std;
typedef pair<int, int> ii;
vector< vector<ii> > AdjList;


int flatten(int ROW_NUM, int row, int col){
    return row*ROW_NUM + col;
}

void showgraph(vector<int> dist, int num_row){
    for(int i = 0; i < dist.size(); i++){
        if(i % num_row == 0) cout << endl;
        cout << dist[i] << " ";
    }
    cout << endl;
}
int main()
{
    int num_row, num_col;
    cin >> num_row >> num_col;
    vector<vector<int> > origin_distances(num_row, vector<int>(num_col));
    vector<vector<int> > connections(257);
    AdjList.resize(num_row*num_col);
    // take input
    for(int i = 0; i < num_row; i++){
        for(int j = 0; j < num_col; j++){
            cin >> origin_distances[i][j];
            if(origin_distances[i][j] > 0){
                connections[origin_distances[i][j]].push_back(flatten(num_row, i, j));
            }
        }
    }

    // construct edges/ neighbours
    for(int i = 0; i < num_row; i++){
        for(int j = 0; j < num_col; j++){
            int neighbour_row = 0;
            int neighbour_col = 0;

            // up
            neighbour_row = i - 1;
            neighbour_col = j;
            if(neighbour_row >= 0){
                if(origin_distances[neighbour_row][neighbour_col] > 0){
                    int black_hole_num = origin_distances[neighbour_row][neighbour_col];
                    for(int k = 0; k < connections[black_hole_num].size(); k++){
                        if(flatten(num_row, neighbour_row, neighbour_col) != connections[black_hole_num][k]){
                            AdjList[flatten(num_row, i, j)].push_back(ii(1, connections[black_hole_num][k]));
                        }
                    }
                }
                else{
                    AdjList[flatten(num_row, i, j)].push_back(ii(1, flatten(num_row, neighbour_row, neighbour_col)));
                }
            }

            // down
            neighbour_row = i + 1;
            neighbour_col = j;
            if(neighbour_row < num_row){
                if(origin_distances[neighbour_row][neighbour_col] > 0){
                    int black_hole_num = origin_distances[neighbour_row][neighbour_col];
                    for(int k = 0; k < connections[black_hole_num].size(); k++){
                        if(flatten(num_row, neighbour_row, neighbour_col) != connections[black_hole_num][k]){
                            AdjList[flatten(num_row, i, j)].push_back(ii(1, connections[black_hole_num][k]));
                        }
                    }
                }
                else{
                    AdjList[flatten(num_row, i, j)].push_back(ii(1, flatten(num_row, neighbour_row, neighbour_col)));
                }

            }

            // left
            neighbour_row = i;
            neighbour_col = j - 1;
            if(neighbour_col >= 0){
                if(origin_distances[neighbour_row][neighbour_col] > 0){
                    int black_hole_num = origin_distances[neighbour_row][neighbour_col];
                    for(int k = 0; k < connections[black_hole_num].size(); k++){
                        if(flatten(num_row, neighbour_row, neighbour_col) != connections[black_hole_num][k]){
                            AdjList[flatten(num_row, i, j)].push_back(ii(1, connections[black_hole_num][k]));
                        }
                    }
                }
                else{
                    AdjList[flatten(num_row, i, j)].push_back(ii(1, flatten(num_row, neighbour_row, neighbour_col)));
                }

            }

            // right
            neighbour_row = i;
            neighbour_col = j+ 1;
            if(neighbour_col < num_col){
                if(origin_distances[neighbour_row][neighbour_col] > 0){
                    int black_hole_num = origin_distances[neighbour_row][neighbour_col];
                    for(int k = 0; k < connections[black_hole_num].size(); k++){
                        if(flatten(num_row, neighbour_row, neighbour_col) != connections[black_hole_num][k]){
                            AdjList[flatten(num_row, i, j)].push_back(ii(1, connections[black_hole_num][k]));
                        }
                    }
                }
                else{
                    AdjList[flatten(num_row, i, j)].push_back(ii(1, flatten(num_row, neighbour_row, neighbour_col)));
                }

            }
        }
    }

    // run algorithm
    int s, V;
    s = 0;
    V = num_row*num_col;
    vector<int> dist(V, INF); dist[s] = 0;
    priority_queue< ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0, s));
    while(!pq.empty()){
        ii node = pq.top(); pq.pop();
        int node_cost = node.first, node_name = node.second;
        if(node_cost == dist[node_name]){
            for(int i = 0; i < AdjList[node_name].size(); i++){
                int neighbour_node = AdjList[node_name][i].second;
                int neighbour_cost = AdjList[node_name][i].first;
                if(dist[neighbour_node] > neighbour_cost + dist[node_name]){
                    dist[neighbour_node] = neighbour_cost + dist[node_name];
                    pq.push(ii(dist[neighbour_node], neighbour_node));
                }
            }
        }
    }
//    showgraph(dist, num_row);
    // print minimum cost
    cout << dist[num_row*num_col - 1] << endl;

    return 0;
}
