//
//  main.cpp
//  Works Application 2016 Travel Information Center
//
//  Created by Raymond Sak on 2/11/2015.
//  Copyright © 2015 Raymond Sak. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>


using namespace std;

struct city {
  bool isFestive = false;
  bool visited = false;
  int depth = 0;
};

int main() {
  
  // 1. Read variables n, m, and n+m-1 lines
  
  int n, m;
  cin >> n >> m;
  vector<vector <int> > input(n+m-1);

  int a, b;

  for (int i = 0; i < n+m-1; i++) {
    cin >> a >> b;
    input[i].push_back(a);
    input[i].push_back(b);
  }
  
  
  // 2. Graph structure to store the cities node
  // Even though that there is only one path between two city -> a tree
  
  vector<city> city(n);
  city[0].isFestive = true;
  
  vector < vector<int> > citygraph(n, vector<int>(0));
  int x, y;
  
  for (int i = 0; i < n-1; i++) {
    x = input[i][0];
    y = input[i][1];
    citygraph[x-1].push_back(y-1);
    citygraph[y-1].push_back(x-1);
  }
  
  
  // 3. Loop through the requests/ announcements
  // Requests: Apply breadth first search to search for shortest path
  // Announcemnts: Change the status of the city
  
  queue<int> wait;
//  int length = 0;
  int temp;
  
  for (int i = n-1; i < n+m-1; i++) {
    x = input[i][0];
    y = input[i][1];

    if (x == 1) {
      // announcement
      city[y-1].isFestive = true;
    }
    else if (x == 2) {
      // requests
      wait.push(y-1);
      while (wait.size() != 0) {
        temp = wait.front();
        if (city[temp].isFestive == true) {
          cout << city[temp].depth << endl;
          queue<int> empty;
          swap(wait, empty);
        }
        else {
          city[temp].visited = true;
          for (vector<int>::const_iterator it = citygraph[temp].begin(); it < citygraph[temp].end(); it++) {
            if (city[*it].visited == false) {
              wait.push(*it);
              city[*it].depth = city[temp].depth + 1;
            }
          }
          wait.pop();
        }
        
      }

      for (int i = 0; i < n; i++) {
        city[i].visited = false;
        city[i].depth = 0;
      }
    }
  }
  
  return 0;
}
