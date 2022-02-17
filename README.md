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

22.01.11 ~ 01.17
- 인벤토리와 관련되어 새로 작성 중
- 컴퓨터 고장으로 메인보드 도착 전까지 ue4 학습

22.01.17
- 파일이 깨져서 프로젝트를 새로 만들고 복구하는 중
- 마음이 아프다

~ 22.01.21
- 깨진 프로젝트 파일들을 전부 복구하였다
- 하는 김에 쓸모없는 파일들을 모두 정리하였고 코드의 리팩토링도 수행하였다
- 복구 과정 중에 링커 오류들에 대처하는 방법도 알아냄
- 이전에 구현하지 못한 좀비의 달리기, 달리는 중 공격을 구현함

22.01.22
- 위젯과 관련하여 vector deleting destructor 문제가 발생한다
- 원인이 무엇인지 정확히 몰라 해결 방법을 찾는 중이다.

~ 22.01.26
- 위젯 문제를 해결하였다. 덤으로 언리얼 파이프라인 학습도 같이 하게 되었다.
- 디폴트 값이 고정되어서 캐릭터의 애니메이션과 조작이 연결되지 않는 문제를 해결하였다.

22.01.27
- 데미지 프레임워크를 통해 플레이어가 좀비에게 받는 데미지 처리를 적용하였다.

22.01.28
- 애니메이션 노티파이, 델리게이트의 broadcast 기능을 사용하여 플레이어에게 적당한 데미지를 주도록 수정하였다.

22.01.29
- 메인 메뉴 위젯과 게임을 연결
- Start 버튼을 눌러 게임으로 진입하도록 만들었다.

22.01.30
- 리스트 뷰를 사용하여 지난번에 못한 인벤토리를 구현하고 있다.

22.01.31
- 리스트 뷰를 통해 인벤토리를 작성하는 것에 성공하였다.
- 아직 인벤토리의 내용물을 출력하는 것은 실패함

~ 22.02.02
- 인벤토리의 내용을 제대로 출력할 수 있게 만들었다.

22.02.03
- 아이템과 플레이어 간 상호작용 구현 중

22.02.04
- 무기 아이템에 위젯을 달고 플레이어와 충돌할 경우 위젯을 출력하는 기능을 추가함

22.02.05
- 델리게이트를 추가하여 캐릭터와 무기 아이템 간 위젯 통신을 구현
- 무기를 획득하려면 아이템에 닿고 상호작용 키를 눌러 진행 바를 채워야 한다.
- 아이템의 콜리전을 벗어나거나 상호작용을 중단하면 진행 바가 초기화된다.

~ 22.02.10
- 인벤토리의 정비 완료
- 인벤토리에 아이템이 없으면 추가, 아이템을 다 소모하면 리스트 상에서 사라지도록 구현함

22.02.11
- 총구 이펙트, 충돌 이펙트 구현, 좀비 사운드 추가
- 좀비를 공격할 시 피가 튀기는 것을 구현하고 싶었지만 무료 FX중에 그런 것이 없어서 구현하지 못해 아쉽다.

~ 22.02.13
- 아이템 파밍용 박스 액터 생성
- 7종류의 아이템을 랜덤하게 생성한다.
- 무기도 파밍할 수 있게 생성할 수 있으므로 이후 추가할 예정

22.02.14
- 문 액터 생성
- 건물에 들어가기 위해서는 문을 열어야 하고 시간을 소모하게 됨

22.02.15
- 총알 정보와 인벤토리, 플레이어 위젯 간 연결로 남은 총알 정보를 갱신하도록 만들었다.
- 재장전 시 인벤토리 상의 총알도 줄어든다.

22.02.16
- 인벤토리에 존재하는 아이템 개수와 관련된 버그들을 수정함
- 아이템 박스를 캐릭터가 뚫고 진행하는 버그도 수정함

22.02.17
- 엔진 컨텐츠를 이용하여 시간이 지나는 것을 구현함
- 시간에 따라서 해가 지고 뜬다
- 맵을 구성하였고 내비메시볼륨을 지정하여 AI가 움직일 수 있도록 만듦

