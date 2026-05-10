import random

def main():
    # 1から3000までのリストを作成
    numbers = list(range(1, 3001))
    
    # リストをランダムにシャッフル
    random.shuffle(numbers)
    
    # 空白区切りの文字列にして出力
    print(" ".join(map(str, numbers)))

if __name__ == "__main__":
    main()
