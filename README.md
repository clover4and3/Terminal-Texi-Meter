# Terminal Taxi Meter

## 1. Project Overview

Linux 시스템 프로그래밍에서 배운 개념을 활용한
터미널 기반 택시 미터기 프로그램.

## 2. Learning Objectives

- Terminal I/O
- stty & termios
- ncurses
- Signal Handling
- setitimer()
- Modular Programming
- Git & GitHub

## 3. Development Environment

- OS: Ubuntu Linux
- Language: C
- Compiler: GCC
- Library: ncurses
- Version Control: Git

## 4. Features

### START Screen
- [ ] 터미널 속성 저장 및 복구
- [ ] ECHO, ICANON 제어
- [ ] 사용자 키 입력 처리
- [ ] 운행 시작 및 종료 메뉴

### RUNNING Screen
- [ ] ncurses WINDOW 화면 분할
- [ ] 말 달리기 애니메이션
- [ ] setitimer() 타이머 설정
- [ ] SIGALRM 처리
- [ ] 택시 요금 계산

### PAY Screen
- [ ] 최종 요금 출력
- [ ] 결제 수단 선택
- [ ] 결제 완료 처리

## 5. Build & Run

```bash
gcc -Wall -Wextra main.c terminal.c ui.c -o taxi -lncurses
./taxi
```

## 6. Project Structure

- main.c : 프로그램 실행 흐름 제어
- terminal.c : 터미널 속성 제어
- terminal.h : 터미널 모듈 인터페이스
- ui.c : 화면 출력 및 UI 관리
- ui.h : UI 모듈 인터페이스

## 7. Development Principles

- 핵심 코드는 직접 작성한다.
- 작성한 코드의 동작 원리를 이해한다.
- AI는 개념 학습, 디버깅, 코드 리뷰에 활용한다.
- 기능별 Git Branch를 생성하여 개발한다.
- 학습한 내용을 손코딩으로 복습한다.
