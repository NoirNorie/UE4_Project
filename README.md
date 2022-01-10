# UE4_Project
- Native C++ 구현 중

21.12.15
- TPS 프로젝트 생성
- 기본 이동 바인딩

21.12.16
- 애니메이션과 행동 연결

21.12.17
- 인터페이스로 블루프린트와 플레이어 캐릭터 연결

21.12.18
- 조준 HUD, 조준 애니메이션 연결

21.12.19
- 조준 애니메이션 시 방향 수정
- 에임 오프셋 구현

21.12.20
- 총 발사 시 소리 추가, 애니메이션 추가

21.12.21
- 재장전과 애니메이션 연결
- 재장전 횟수 제한 구현

21.12.22
- 위젯 생성
- 위젯 생성 시 출력되는 에러 수정
- 플레이 맵 생성 중

21.12.23
- 1차 코드 리팩토링
- 코드 내 불필요한 부분 제거

21.12.24
- 캐릭터 외형 임포트 및 애니메이션 입력

21.12.25
- 블랙보드, 비헤이비어트리 생성
- 비헤이비어트리에 에러 존재
- 좀비 에셋, 애니메이션 임포트

21.12.26
- 비헤이비어 트리, 블랙보드 에러 수정
- 비헤이비어 트리, 블랙보드 활성화 확인
- 비헤이비어 트리, 블랙보드, 좀비와 연결 확인
- 좀비의 이동과 정지, 애니메이션 연결

21.12.27
- 비헤이비어 트리, 블랙보드 수정
- 좀비가 캐릭터 추적을 가능하도록 노드를 만들어 구현

21.12.28
- 좀비가 공격, 추적을 가능하도록 노드를 만들어 구현
- 지속적으로 캐릭터를 추적하고 공격하도록 만들었다

21.12.29
- 4종류의 언리얼 델리게이트 학습
- 비헤이비어 트리와 노드들의 수정작업
- 투사체를 만들었지만 직선으로 나아가지 않아 수정이 필요함

21.12.30
- 투사체를 직선으로 나아가도록 수정함
- 중력 값이 0.1, 투사체 속도는 20,000으로 보이는 구간에서는 직선으로 움직이는 것으로 보임
- 투사체가 크로스헤어와 같은 방향을 향하지 않는 문제가 있음
- 비슷하지만 정확히 일치하지 않음, 크로스헤어 중심으로 좌상단을 향하여 발사됨

21.12.31
- 투사체가 총에서 발사되는 것처럼 만들기 위해 총의 스켈레탈 메시에 소켓을 뚫어서 위치를 받아냄
- 총이 움직이는대로 총알이 발사되도록 만듦

22.01.01
- 무기 클래스들을 추가하여 습득하는 무기에 따라 들고있는 무기가 변경되도록 만듦
- 무기 에셋들을 구한다면 추가적으로 구현할 수 있을 것 같음

22.01.02
- 총알에 데미지를 추가하여 좀비에 충돌 시 데미지 처리 진행 중
- 좀비와 총알 데미지 처리에 충돌(엔진이 종료됨)

22.01.03
- 총알과 좀비 사이에 넘쳐나는 버그 해결
- 좀비가 사망 후에도 캐릭터의 방향으로 회전하는 문제 해결
- 데미지가 사망 후에도 처리되어 충돌이 나는 문제 해결

22.01.04
- 탄창과 캐릭터의 인터페이스 함수 생성
- 캐릭터가 탄창을 주우면 현재 들고 있는 무기의 탄창을 증가시키도록 만듦

22.01.05
- 맵과 플레이어의 탄창 획득 과정을 정리
- 무기 발사 시 크로스헤어와 일치하지 않는 문제 수정 중

22.01.06
- 플레이어 캐릭터의 계층 구조 정돈
- 카메라 이름의 문제로 우클릭 시 충돌이 나는 문제 해결

22.01.07
- 조준점과 투사체의 방향이 일치하지 않는 문제를 해결하기 위해 투사체 발사 방식이 아닌 히트스캔 방식으로 수정
- 데미지 프레임워크를 이용하여 처리

22.01.08
- 무기 아이템을 획득할 경우 데미지와 연사력이 변경되도록 구현
- 인터페이스 함수의 구현과 통신 방식에 대해서 좀 더 배우게 되었다

22.01.09
- 무기 1개를 더 추가하였고 사운드 큐를 사용해 무기마다 사운드가 다르게 출력되도록 만들려고 함
- 사운드 큐와 관련되어 문제가 있어 좀 더 시간이 필요할 것 같음

22.01.10
- 사운드 큐와 관련된 문제들을 해결하고 수정함
- 무기마다 다른 사격음이 출력되도록 만듦
- 인벤토리 제작 중

22.01.11
- 인벤토리와 관련되어 새로 작성 중
