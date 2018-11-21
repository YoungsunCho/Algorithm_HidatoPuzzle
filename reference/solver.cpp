#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <cstring>

//추가sdkjflsdkj
//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
struct node
{
    int val;
    unsigned char neighbors;
};
//------------------------------------------------------------------------------
class hSolver
{
public:
    hSolver()
    // row, col을 받아서 8가지 방향을 정해준다
    {
    	dx[0] = -1; dx[1] = 0; dx[2] = 1; dx[3] = -1; dx[4] = 1; dx[5] = -1; dx[6] = 0; dx[7] = 1;
    	dy[0] = -1; dy[1] = -1; dy[2] = -1; dy[3] = 0; dy[4] = 0; dy[5] = 1; dy[6] = 1; dy[7] = 1;
    }

    // 여기가 메인 함수 퍼즐과 width를 파라미터로 받음
    void solve( vector<string>& puzz, int max_wid )
    {
    	if( puzz.size() < 1 ) return;
    	wid = max_wid;
      // 높이를 퍼즐크기 / width로 해서 구함
      hei = static_cast<int>( puzz.size() ) / wid;
      // 크기, c, max 0
    	int len = wid * hei, c = 0; max = 0;
      // 크기만큼의 노드 선언
    	arr = new node[len]; memset( arr, 0, len * sizeof( node ) );
      // 퍼즐에서 알려준 숫자를 표현하기위해 bool 타입의 array를 선언
      weHave = new bool[len + 1]; memset( weHave, 0, len + 1 );

      // puzzle의 시작부터 끝까지 루프
      // arr, weHave 1차원 배열로 초기설정하기 위한 for문이다.
    	for( vector<string>::iterator i = puzz.begin(); i != puzz.end(); i++ )
    	{
          // c는 인덱스인데 그거를 증가시켜가며 * 즉, 벽일경우 -1로 설정
    	    if( ( *i ) == "*" ) {    arr[c++].val = -1; continue; }
          // c_str()은 string을 char * 형태로 변환
          // atoi는 char*을 int로 변환
          // 벽이 아닐경우 값을 저장해 주는 것이다. 1차원 배열로!
          arr[c].val = atoi( ( *i ).c_str() );
          // 0보다 클경우 weHave, 즉 나와져 있는 수는 true로 저장해주는것이다.
          if( arr[c].val > 0 ) weHave[arr[c].val] = true;
          // max값 저장
    	    if( max < arr[c].val ) max = arr[c].val;
    	    c++;
    	}

      // 여기서 solveIt으로!
    	solveIt();
      c = 0;
      // .인 빈칸들을 arr 1차원 배열로 다 채우기~
    	for( vector<string>::iterator i = puzz.begin(); i != puzz.end(); i++ )
    	{
    	    if( ( *i ) == "." )
    	    {
    		ostringstream o; o << arr[c].val;
    		( *i ) = o.str();
    	    }
    	    c++;
    	}
      // garbage collection 반환~~~~
    	delete [] arr;
    	delete [] weHave;
    }

private:
    // 시작점 찾은 후 실행되는 함수
    bool search( int x, int y, int w )
    {
       // w는 몇번째 숫자인지 확인하는 것이다.
       // 마지막점이면 종료
	     if( w == max ) return true;

       // 임시노드 n은 시작점의 포인터 갖고있음.
	     node* n = &arr[x + y * wid];
       // n의 이웃 찾기
	     n->neighbors = getNeighbors( x, y );
       // 우리가 가지고 있으면
	     if( weHave[w] )
	     {
          // 이웃들 확인하기위해 8번 돌림
	        for( int d = 0; d < 8; d++ )
	        {
              // 만약에 이웃이 있다면
		          if( n->neighbors & ( 1 << d ) )
		          {
                // a랑 b를 다시 설정
        		    int a = x + dx[d], b = y + dy[d];
                // 이웃의 값이 w와 같으면
                if( arr[a + b * wid].val == w )
                  // recursive하게 계속
                  if( search( a, b, w + 1 ) ) return true;
		          }
	        }
	        return false;
	      }
        // 가지고 있는 숫자가 아닌경우
        // 한번더 이웃비교?
	      for( int d = 0; d < 8; d++ )
	      {
           //이웃이 있으면
	         if( n->neighbors & ( 1 << d ) )
	         {
               // a, b다시 설정
		           int a = x + dx[d], b = y + dy[d];
               // 빈칸이면
		           if( arr[a + b * wid].val == 0 )
		           {
                   // 임의의점을 w로 설정해준다.
        		       arr[a + b * wid].val = w;
                   // 그 점을 통해 다시 recursive
        		       if( search( a, b, w + 1 ) ) return true;
                   // recover 실패할경우를 대비해 recover해줌
        		       arr[a + b * wid].val = 0;
		           }
	         }
	      }
	      return false;
       }

    // search에서 이웃찾기 위해 온 함수
    unsigned char getNeighbors( int x, int y )
    {
    	unsigned char c = 0;
      int m = -1, a, b;
      // 3번인데 무조건? -1 0 1
    	for( int yy = -1; yy < 2; yy++ )
	      for( int xx = -1; xx < 2; xx++ )
	      {
            // 8방향을 만들기 위해 같을때 즉, 본인의 점일때는 스킵
		        if( !yy && !xx ) continue;
            //
		        m++;
            // a로 x방향, b로 y방향 업데이트
            a = x + xx, b = y + yy;
            // 매트릭스 바깥으로 나갈경우 스킵
		        if( a < 0 || b < 0 || a >= wid || b >= hei ) continue;
            // 비트 OR (inclusive or)
            // m이 몇번째 비트인지 설명하는 것이고
            // 아 비트로 8비트 ex) 0 0 0 1 0 0 0 0 이면 4번째 방향만 갈수 있는 것이다.
            if( arr[a + b * wid].val > -1 ) c = c |( 1 << m );
	      }
	    return c;
    }
    // solve함수에서 첫번째로 불려지는함수, start point찾고 search시작
    void solveIt()
    {
      //빈 int선언하고 레퍼런스로 파라미터 넘겨줘서 찾는것도 가능하네... ㄷㄷ
    	int x, y; findStart( x, y );
      // 찾지 못했을 경우 -1로 설정된다
      if( x < 0 ) { cout << "\nCan't find start point!\n"; return; }
      // 찾으면 x는 width, y는 height이다.
      search( x, y, 2 );
    }

    // 시작점 찾는 함수
    void findStart( int& x, int& y )
    {
	    for( int b = 0; b < hei; b++ )
	    for( int a = 0; a < wid; a++ )
      // 1차원 배열로 선언해놔서 a + wid * b로 접근.
		  if( arr[a + wid * b].val == 1 ) { x = a; y = b; return; }
	    x = y = -1;
    }

    // 넓이, 높이, 마지막값? 맥스?, 방향 8가지
    int wid, hei, max, dx[8], dy[8];
    // 2차원 매트릭스를 1차원으로 숫자를 저장하기위함
    node* arr;
    // 가지고 있는 수
    bool* weHave;
};
//------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    int wid;
    string p = ". 33 35 . . * * * . . 24 22 . * * * . . . 21 . . * * . 26 . 13 40 11 * * 27 . . . 9 . 1 * * * . . 18 . . * * * * * . 7 . . * * * * * * 5 ."; wid = 8;
    //string p = "54 . 60 59 . 67 . 69 . . 55 . . 63 65 . 72 71 51 50 56 62 . * * * * . . . 14 * * 17 . * 48 10 11 * 15 . 18 . 22 . 46 . * 3 . 19 23 . . 44 . 5 . 1 33 32 . . 43 7 . 36 . 27 . 31 42 . . 38 . 35 28 . 30"; wid = 9;
    //string p = ". 58 . 60 . . 63 66 . 57 55 59 53 49 . 65 . 68 . 8 . . 50 . 46 45 . 10 6 . * * * . 43 70 . 11 12 * * * 72 71 . . 14 . * * * 30 39 . 15 3 17 . 28 29 . . 40 . . 19 22 . . 37 36 . 1 20 . 24 . 26 . 34 33"; wid = 9;

    istringstream iss( p ); vector<string> puzz;
    copy( istream_iterator<string>( iss ), istream_iterator<string>(), back_inserter<vector<string> >( puzz ) );
    hSolver s; s.solve( puzz, wid );

    int c = 0;
    for( vector<string>::iterator i = puzz.begin(); i != puzz.end(); i++ )
    {
	    if( ( *i ) != "*" && ( *i ) != "." )
	    {
	    if( atoi( ( *i ).c_str() ) < 10 ) cout << "0";
	    cout << ( *i ) << " ";
	    }
	    else cout << "   ";
	    if( ++c >= wid ) { cout << endl; c = 0; }
    }
    cout << endl << endl;
    return system( "pause" );
}
//--------------------------------------------------------------------------------------------------
