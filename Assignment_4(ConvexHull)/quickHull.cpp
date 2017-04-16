#include<bits/stdc++.h>
using namespace std;
struct Point{
	double x, y;
};
void print_point(Point p){
	cout<<p.x<<" "<<p.y<<endl;
}
int area(Point p, Point q, Point r){
	return abs( p.x*(q.y-r.y) + q.x*(r.y-p.y) + r.x*(p.y-q.y) );
}
double cal_dis(Point p, Point q, Point r){
	double num,den;
	num = area(p, q, r);
	return num;
}
Point *convex_hull_set;
int h=0;
int get_sign(Point A, Point B, Point X){
	int sign = (A.y-B.y)*X.x + (B.x-A.x)*X.y + (B.y*A.x-A.y*B.x);
	if(sign>0) return 1;
	if(sign<0) return -1;
	return 0;
}
void FindHull(Point *point, int n, Point A, Point B){
	if(n<=0) return;
	int index=0, max_dis, temp_dis;
	for(int i=0;i<n;i++){
		temp_dis = cal_dis(A, B, point[i]);
		if(i==0) max_dis=temp_dis;
		else if(temp_dis > max_dis){
			max_dis = temp_dis;
			index = i;
		}
	}
	convex_hull_set[h++]=point[index];
	Point C = point[index];
	Point G;
	G.x = (A.x + B.x + C.x)/3;
	G.y = (A.y + B.y + C.y)/3;
	int sign = get_sign(A, C, G);
	Point *point_pos = new Point[n];
	Point *point_neg = new Point[n];
	int p=0, q=0;
	for(int i=0;i<n;i++){
		if(sign*get_sign(A,C,point[i]) < 0) point_pos[p++]=point[i];
	}
	sign = get_sign(B, C, G);
	for(int i=0;i<n;i++){
		if(sign*get_sign(B,C,point[i]) < 0) point_neg[q++]=point[i];
	}
	FindHull(point_pos, p, A, C);
	FindHull(point_neg, q, C, B);
}

int main(){
	int n;
	cout<<"Enter the no. of points = ";
	cin>>n;
	Point *point = new Point[n];
	convex_hull_set = new Point[n];
	cout<<"Enter the "<<n<<" points:\n";
	int leftmost=0, rightmost=0;
	for(int i=0;i<n;i++){
		cin>>point[i].x>>point[i].y;
		if(point[i].x < point[leftmost].x) leftmost=i;
		if(point[i].x > point[rightmost].x) rightmost=i;
	}

	clock_t t;
	t=clock();
	Point *point_pos = new Point[n];
	Point *point_neg = new Point[n];
	int A,B,C;
	A = point[leftmost].y - point[rightmost].y;
	B = -point[leftmost].x + point[rightmost].x;
	C = point[rightmost].y*point[leftmost].x - point[leftmost].y*point[rightmost].x;
	int p=0, q=0, val;
	for(int i=0;i<n;i++){
		if(i!=leftmost && i!=rightmost){
			val = A*point[i].x + B*point[i].y + C;
			if(val>0){
				point_pos[p++]=point[i];
			}
			if(val<0){
				point_neg[q++]=point[i];
			}
		}
	}
	convex_hull_set[h++] = point[leftmost];
	convex_hull_set[h++] = point[rightmost];
	FindHull(point_pos, p, point[leftmost], point[rightmost]);
	FindHull(point_neg, q, point[leftmost], point[rightmost]);
	t=clock()-t;
	cout<<"Convex hull :\n";
	cout<<"h = "<<h<<endl;
	for(int i=0;i<h;i++){
		print_point(convex_hull_set[i]);
	}
	printf ("%f seconds\n",t, ((float)t)/CLOCKS_PER_SEC);
	return 0;
}
