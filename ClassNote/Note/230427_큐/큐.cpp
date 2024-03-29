/*
	중간 고사 : 5월 중순이나 말 쯤에 볼 듯?
	tree도 시험 범위에 넣으려고
	시험 문제 내는 스타일 -> 매우 중요한거라고 집중해라 하는건 이미 다 안다고 생각한다.
	교수님은 이미 우리를 공부를 열심히 하는 학생이라고 생각한다고 가정. 
	-> 중요한건 이미 다 알텐데 뭐하러 시험으로 내?

	시험 문제를 낼 때? 문제내는 목표
	1. 이 과목에서 중요한 내용을 알고 있는지 -> 이미 안다! 라고 생각
	2. 노력의 차등을 평가에서도 차등할 수 있게
	3. 공부를 더 한 학생을 구분하기 위해서
	
	공부해 올 내용 - 성능 분석, 책을 사오는걸 추천, 가장 중요한 파트 미리 공부해와라.
	공간복잡도 - 고정공간사용량이란?, 가변공간사용량이란?
	시간복잡도 - 시간을 어떻게 측정하는 것이 좋을까?, Big O 표기법



	DS10 : 5월 5일 실습 문제 => 자료 구조 시험중 가장 어려운 문제다 어쩄든 잘 구현해야 할 거다.
	5월 5일, 5월 8일에 시험 형식으로 하지 않고 과제 형식으로 하겠다.
	5월 5일까지 집에서 완성 시켜라.==>5월 8일까지
	한 칸 띈 돌세기. 가장 길게 연속된거 좌표 출력해라.
	(빈칸 만나면 ++해보고 다음께 같은 돌이면 다시 카운트 시작하고 다른 돌이면 그대로 카운트 끝내는 구현?)
	ㅇㅇㅁㅇ -> 3개로 치는 거
	ㅇㅇㅁㅇㅇㅁㅇㅇ -> 4개 연속이라고 침.
	ㅇㅁㅇㅇㅁㅇㅇ -> 이것도 4개 연속
	==>ㅇㅁㅇㅇ, ㅇㅇㅁㅇㅇ 두갈래 모두 따져봐야 됌.
	전체에서 제일 긴거, 만약 3개짤기ㅏ 여러개 있으면 그거 모두 출력

	상태변환도
	연속없음, 검은돌연속, 흰돌연속, 한칸띈 검은돌 연속, 한칸 띈 흰돌 연속
	-> 이그림 만으론 사이 빈칸 2개가 처리가 안됌


	오목 배틀 프로그램을 어떻게 작성하는 지
	함수 4개
	White Attack(내가 놓는 돌의 위치를 심판에게 알려줌), Defence(상대방의 놓는 돌의 위치를 내 보드에 놓음)
	Black Attack, Defence
	심판, 예제 프로그램 올려줄거임,
	Omock_학번.h로 만들기
	함수 이름은 뒤에_학번 붙이기 변수 겹치니까.

	오목 배틀 수행 요령
	조원과 모두 같이 오목 게임 수행(게임 횟수 한명 당 총 4회, 합의 되면 AI 수정하고 재배틀 가능)
	오류패, 부전패, 불참패 있음 같은 패배라도 차등해서 줌, 게임을 하면 승자랑 패자랑 크게 차이 안날꺼임.
	참여가 중요함
	심판 프로그램이 버그 나면 무승부

	조장에게 6월 20일까지 제출
	6월 21일까지 조원들에게 다시 보냄
	6월 21일까지 조원들은 동일한 조별 배틀 수행 결과 보고서 제출.
	소스콛, 설계보고서, 팀프 수행 소감.


	

	*큐 설명
	Ex) lower 0 front 2 rear 6 upper 10
	Enqueue : rear뒤에 하나 씩 들어가고 rear + 1 될 것이다.
	Dequeue : front뒤에 하나씩 삭제하고 front + 1

	lower = 0, upper = 10
	Full : 꽉 차 있을 때 front = -1 //  rear = 10	//1차 가정
	Empty : 비어 있을 때 front = -1 //  rear = -1

	ㅁㅁㅇㅇㅇㅇㅇ//앞에만 비어있어서 Enqueue를 할 수 없는 상황이 생김.
	lower 0 front 1 rear 6 upper 6

	Q. 이 문제를 어떻게 해결할 것인가?
	Solution1. Dequeue를 할 떄마다 매번 땡겨주면 되지 않나?
	->자료가 너무 많으면 Dequeue 할 때마다 연산을 너무 많이 해줘야 한다.

	Solution2. Enqueue할 때 뒤까지 다 막혀 있는데, 앞이 비어있으면 그 때만 땡겨준다.
	->안하면 안될 때 하려고.// 컴퓨터에선 이렇게 작업 하는게 효율적임.

	Solution3. 아에 떙기지 말고 환형큐로 뒤에가 꽉 차있으면 
	q[0]부터 집어 넣어버리고 q[1]부터 시작이라고 한다.
	->앞에서부터 집어 넣을 때, lower 0->1 upper 10->0으로 바꿔버리면 문제가 없지 않을까?
	=> Full 상태 Empty 상태 검사 front와 rear의 값이 동일 해질 떄 Full 상태, Empty 상태 또한 rear와 front 값이 동일 할 때.


	Q1. 그럼 Full Empty의 판단 여부는? 
	1. 가장 직전에 실행 명령이 Dequeue면 Empty, Enqueue면 Full
	2. 그 안의 값이 없으면 Empty, 있으면 Full
	3. => 보통 12개 넣고 11개만 넣고 꽉찼다고 친다.
	4. ==> 교수님이 선호하는 방법 Enqueue 할 때 마다 count하는 방법
	*아무튼 추가 정보가 필요 할 것이다.
	
	Empty의 조건
	front == -1 && rear == -1 <- 이건 아님
	front == rear <- 이게 Empty의 조건

	Q2. 환형 큐를 단반향 환형연결리스트로 구현한다면?
	-> 답은 알아서 구현해라 ===> 이런게 시험에 나온다. 일부로 안알려주는 거다.
	그림그리고 구현해본 그룹이 점수 먹게끔 한다.

	Q3. 이것도 문제러 줬으니까 봐라


*/