/*
	그래프
	무방향성 그래프 : (1,2) 방향이 업음
	방향성 그래프 : <1,2> 1->2를 가리키고 있음
	V(G) = {1,2,3,4,5,6}//버텍스의 집합
	E(G) = {<1,2>,<3,1> *** }//엣지의 집합
	V, E는 동일한 그래프다

	트리냐 그래프냐에 따라서 동일할 수도 있고 다를 수도 있다(그래프는 층위를 따지진 않지만, 트리는 층위를 따진다)

	그래프의 기본 용어
	인접하다 : 정점에서 간선으로 연결된 다른 정점, 암튼 연결됐다.
	부속하다 : 정점에 연결된 간선, 딸려 있다. 엣지에게 사용하는 용어 ex) e선은 A노드, B노드에 부속되어 있다.
		
	트리의 그래프의 차이점 2 : 노드의 차수는 연결된 모든 노드, 트리는 자식 노드
	주어진 그래프에서 노드의 차수, 그래프의 차수가 다르다
	시허에서 주어진 그래프의 총 차수, 그래프의 차수의 합은 다르다
	진입차수, 진출 차수 추가 공부좀

	경로(path) : 임의의 정점으로부터 목적지까지 이르는 간선들의 집합(경로의 정의를 아는지 기말에서 물어보고 싶다.)
	경로의 정의를 써라, 그림을 주고 어디부터 어디까지 가는 경로를 표현해라
	
	{1,2,5}라고 쓰면 틀린거임. 지금 수업시간에 강조하고 있잖아
	1부터 5까지의 경로 {(1,2), (2,5)}
	정점 1에서 6까지의 경로의 개수
	1,3 3,6 // 1,2 2,5 5,3 3,6 // 1,2 2,4 4,2 2,5 5,3 5,3 3,6 // 등등 모두 다 경로다.
	경로의 개수는 미친듯이 많다
		1
	   2 3
      4 5 6

	경로의 길이 : 경로 상에 존재하는 간선의 수 1,2 3,6 길이 : 2 // 1,2 3,6 6,3 3,5 길이 : 4
	단순 경로 : 처음과 어 못씀...
	사이클 : 처음과 끝 정점이 동일한 단순 경로, 트리가 아ㅣㄴ다
	비순환 그래프 : 사이클을 포함하지 않는 경로

	완전 그래프 : 엣지를 그릴 수 있는대로 빽뺵하게 그린게 완전그래프다.
	무방향성 완전 그래프
	정점의 수 n
	간선의수 nC2 = n(n-1)/2

	방향성 완전그래프
	전체 간선의 수 : nP2 = n(n-1)
	무방향성보다 2배 많다.

	버텍스의 개수가 n이면 엣지의 개수는 n^2로 늘어난다.
	알고리즘 만들 떄 버텍스의 개수에 따라서랑 엣지의 개수에 따라서 만들 때
	버텍스에 따라서 만드는게 좋은 알고리즘이다.

	부분 그래프 : 버텍스, 엣지의 집합이 모두 들어가 있으면 부분그래프다. 간단함

	그래프의 구현 방법
	배열 형태로는 구현하기 힘들다, 포인터로 구현하면 어떨까?
	백진트린데 사향트리면? 메모리 낭비 개심하네???
	그래프에서는 완전 그래프같은건 없다
	페이스북 가입자 전부가 서로 팔로잉 팔로워 하고 있다는 소리임

	모든 그래프의 모양은 느슨하게 연결되어 있을 것이다.
	트리 방식으로도 구현을 못하겠구나

	그래프의 표현 방법
	인접 행렬, 인접리스트
	인접행렬
	행렬로 버텍스 6게먄 6*6행렬로 표현해서 1-2가 엣지가 있으면 1로 표현 없으면 0으로 표현한다.
	문제점 : 버텍스의 개수 만큼 선언을 해줘야 한다. 0들어간거, 엣지가 없다는걸 표현하기 위해 메모리 낭비하는게 너무 아깝다.  // 수강과목만 나오는게 아니라 수강 안한 모든 과목들까지 다 뜨면 개빡칠거잖아
	2. 무방향성 그래프는 : 절반은 필요 없잖아
	3. 배열로 구현하면 크기가 고정 되어 있잖아. 버텍스가 추가되면 어쩔껀데 -> 그래서 연결리스트

	인접리스트
	없는거 표현하지 말자랑 크기 고정은 해결 된듯?
	인접리스트도 배열이 있잖아

	직접 그려봐 그럼 쉬워

	그래프의 운행
	그래프도 모든 데이터를 다 뒤져봐야 한다.
	깊이 우선탐색, 너비 우선 탐색

	깊이 우선 탐색 : 시작점부터 여러 갈래길이 있는데 한길을 정해서 거기로 가 길이 더이상 갈 수 없을 떄까지(길이 없거나, 그 길을 따라가면 이미 왔던대면)
	갈 길이 없으면 한칸 돌아가, 안간 길이 있으면 거기로 가
	돌아가다가 처음 자리로 돌아오게 되면 끝남.
	-모든 노드를 방문한다는게 증명 됐다

	너비 우선 탐색 : 나랑 거리인 1인 노드 다 보고, 2인 노드 다 보고 노드가 안나올 떄 까지 간다
	-이 방법도 모든 노드를 다 볼 수 있다.
	이것도 시험 문제에 나오 겠지?

	=== 이런게 있다
	신장트리 - 심시티를 할 때 우리가 짠 AI로 한다면?
	전기줄 - 엣지로 표현되겠지?
	정점의 수가 N일 때 n-1(최소한의 선의 개수)개의 선으로 연결해봐라

	신장트리 예
	DFS 신장트리(깊이우선탐색), BFS 신장트리(너비 우선 탐색)

	최소 신장 트리
	엣지에 데이터 값이 들어갈 수 있다.
	전기줄을 건설하는데 중간에 물이, 산이, 산적 때가 있어서 1원이 100원이 될 수 도 있고 못건설할 수도 있다.
	
	최소 신장 트리는 가중치의 최소한의 합으로 연결하는 거.
	
	쿠루스칼의 방법
	가중치가 가장 작은 간선을 오름차순으로 정리해서 사이클이 생기지 않게 검사하면서 안생기면 넣음
	이거 n^2 log n 인데? 개많은데?

	모든 버텍스의 대해서 나의 다른 모든 버텍스의 거리를 계산한다.
	이건 n^2이다.
	조금더 좋긴 함.

	다음주 준비해야할 내용
	정렬에 대해 공부해야할 것
	정렬의 종류, 각 방법의 시간 복잡도는?
	그냥 개념적으로 보겠다.
	타임컴플렉스 몇개 대표적으로만 보겠다.
	더 중요한 거는 퀵정렬은 언제 쓰는가? 버블정렬은 아무짝에도 쓸모 없는 것이낙?
	삽입정렬을 언제 쓰면 아노디나, 이게 어떤게 좋은가?

	실습 문제
	중간고사 끝나고 조를 발표하겠다.
	각 조마다 중간고사 점수로 균등하게 한다.
	조장도 지정하겠다.
	실습시간에 배틀 준비해라.

	시험은 괜찮은데 도전!!해야 도전임.

*/