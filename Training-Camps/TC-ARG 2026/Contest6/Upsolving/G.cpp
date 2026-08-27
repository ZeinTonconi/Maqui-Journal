#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
struct Point{
  int x,y;
  int civ;
  int id;
};

int crossProduct(const Point &O, const Point &A, const Point &B){
  return (A.x-O.x)*(B.y-O.y)-(A.y-O.y)*(B.x-O.x);
}

vector<Point> getConvexHull(vector<Point> &pts){
  int n=pts.size(),k=0;
  if(n<=1) return pts;
  vector<Point> hull(2*n);

  sort(pts.begin(),pts.end(),[](const Point &a,const Point &b){
    return a.x<b.x || (a.x==b.x && a.y<b.y);
  });

  for(int i=0;i<n;i++){
    while(k>=2 && crossProduct(hull[k-2],hull[k-1],pts[i])<=0) k--;
    hull[k++]=pts[i];
  }

  for(int i=n-2,t=k+1;i>=0;i--){
    while(k>=1 && crossProduct(hull[k-2],hull[k-1],pts[i])<=0) k--;
    hull[k++]=pts[i];
  }
  hull.resize(k-1);
  return hull;
}
vector<ii> roads;

bool isInsideTriangle(Point A,Point B,Point C,Point P){
  int cp1=crossProduct(A,B,P);
  int cp2=crossProduct(B,C,P);
  int cp3=crossProduct(C,A,P);

  if(cp1>0 && cp2>0 && cp3>0) return 1;
  if(cp1<0 && cp2<0 && cp3<0) return 1;
  return 0;
}

void solveRegion(Point A,Point B,Point C, vector<Point> &interior){
  if(interior.empty()) return;

  Point anchor=interior[0];
  cout<<"Region "<<A.id<<" "<<B.id<<" "<<C.id<<" "<<anchor.id<<":\n";
  for(auto &v:interior) cout<<v.id<<" ";
  cout<<endl;
  
  if(anchor.civ==A.civ) roads.push_back({anchor.id,A.id});
  else if(anchor.civ==B.civ) roads.push_back({anchor.id,B.id});
  else roads.push_back({anchor.id,C.id});

  vector<Point> t1,t2,t3;
  for(int i=1;i<interior.size();i++){
    Point p=interior[i];
    if(isInsideTriangle(A,B,anchor,p)) t1.push_back(p);
    else if(isInsideTriangle(B,C,anchor,p)) t2.push_back(p);
    else if(isInsideTriangle(C,A,anchor,p)) t3.push_back(p);
  }

  solveRegion(A,B,anchor,t1);
  solveRegion(B,C,anchor,t2);
  solveRegion(C,A,anchor,t3);
  
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n; cin>>n;
  vector<Point> pts(n);
  for(int i=0;i<n;i++){
    cin>>pts[i].x>>pts[i].y>>pts[i].civ;
    pts[i].id=i;
  }

  if(n<=2){
    if(n==1) cout<<"0\n";
    else{
      if(pts[0].id!=pts[1].id) cout<<"1\11 2\n";
      else cout<<"0\n";
    }
    return 0;
  }

  vector<Point> hull=getConvexHull(pts);
  for(auto &v:hull) cout<<v.x<<" "<<v.y<<" "<<v.id<<" "<<v.civ<<endl;
  int h=hull.size();

  vector<bool> inHull(n,0);
  for(auto &v:hull) inHull[v.id]=1;

  vector<Point> interior;
  for(int i=0;i<n;i++){
    if(!inHull[pts[i].id])
      interior.push_back(pts[i]);
  }

  int trans=0;
  vector<int> transId;
  for(int i=0;i<h;i++){
    int next=(i+1)%h;
    if(hull[i].civ!=hull[next].civ){
      trans++;
      transId.push_back(i);
    }
  }

  if(trans>2){
    cout<<"Impossible\n";
    return 0;
  }
  if(trans==0){
    for(int i=0;i<h-1;i++){
      roads.push_back({hull[i].id,hull[i+1].id});
    }
    int opposite=-1;
    for(int i=0;i<interior.size();i++){
      if(interior[i].civ!=hull[0].civ){
	opposite=i;
	break;
      }
    }

    if(opposite==-1){
      for(auto &p:interior){
	roads.push_back({p.id,hull[0].id});
      }
    } else{
      Point center = interior[opposite];
      interior.erase(interior.begin()+opposite);

      for(int i=0;i<h;i++){
	int next=(i+1)%h;

	vector<Point> region;
	for(auto &p:interior){
	  if(isInsideTriangle(hull[i],hull[next],center,p)){
	    region.push_back(p);
	  }
	}
	solveRegion(hull[i],hull[next],center,region);
      }
    }
  } else{
    for(int i=0;i<h;i++){
      int next=(i+1)%h;
      if(hull[i].civ!=hull[next].civ){
	roads.push_back({hull[i].id,hull[next].id});
      }
    }

    int idA=transId[0];
    int idB=transId[1];
    Point transA=hull[idA];
    Point transB=hull[idB];

    for(int i=0;i<h;i++){
      int next=(i+1)%h;
      if(hull[i].civ==hull[next].civ){
	Point target=(hull[i].civ==transA.civ)?hull[idB%h]:hull[idA%h];

	cout<<hull[i].id<<" "<<hull[next].id<<" "<<target.id<<endl;
	vector<Point> region;
	for(auto &p:interior){
	  if(isInsideTriangle(hull[i],hull[next],target,p))
	    region.push_back(p);
	}
	for(auto &v:region) cout<<v.id<<" ";
	cout<<endl;
	
	solveRegion(hull[i],hull[next],target,region);
      }
    }
  }
  cout<<roads.size()<<"\n";
  for(auto &v:roads) cout<<v.first+1<<" "<<v.second+1<<"\n";
  
  
}
