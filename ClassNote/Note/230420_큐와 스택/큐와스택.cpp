/*
	4/28 실습 문제
	오목에서 다음 기능을 구현해라 DS9
	1. 현재 상태를 저장하는 기능
	어떻게 세이브할 지는 알아서
	2. 저장 파일을 불러 읽어서 다시 플레이 한다.
	3. U를 누르면 한 수씩 "무르기"가 수행되도록 하는 기능 - 여러번 수행되야 함 
	배열이나 연결리스트로 만듦 -> 연결리스트 추천
	4. 무르기의 무르기 스택을 하나 더 만든다 팝한다음에
	다른 스택에다가 넣어놓는다. 무르기의 무르기를 하면 다시 꺼내온다.

	미리 올려놓거나 DS7꺼 올려라.

	무르다가 다시 돌을 두기 시작하면 물렀던 것들은 사라지게 ㅇㅇ
	12345->123 (45) -> 123 6넣으면 (45)사라짐
	
	이문제의 목적
	1. 파일의 입출력
	2. 스택 구현할 줄 알아야 하낟.
	3. 스택과 큐도 별거 아닌거 같아도 게임에서 실제로 쓰는 기능 이다.

	1,2번은 같이가는 거

	스택과 큐는 데이터의 내용이 아닌 들어오는 순서로만 출입을 관리하겠다 라는 뜻.
	
	Push 
	1. Overflow Check
	2. sp 다음 위치에 삽입
	3. sp 조정

	Pop
	1. Underflow Check
	2. sp위치에서 삭제
	3. sp 조정

	ppt에서 스택 구조를 구성하는 방법 알아보기
	팝 푸시에서 차이가 남

	2안으로 구현해야 한다.

	Enqueue
	1. full check
	2. rear 다음 위치에 삽입
	3. rear 조정

	- front, rear 앞, 뒤 포인턱 필요하다
	들어올 때는 rear 부분으로 들어온다
	나갈 때는 front 부분으로 나간ㄷ.



	Dequeue
	1. Empty Check
	2. front 주정
	3. front 위치에서 삭제
*/