#!/bin/bash
# Путь к исполняемому файлу (при необходимости измените)
EXEC=./cub3D

# Функция для тестирования карты
# Принимает 2 аргумента: директория (good или bad) и ожидаемый результат ("good" или "bad")
test_maps_in_dir() {
    local dir="$1"
    local expected="$2"
    local pass_count=0
    local fail_count=0

    echo "Тестирование карт в директории: $dir"
    for file in "$dir"/*.cub; do
        echo "----------------------------------------------------"
        echo "Проверяем: $file"
        # Для хороших карт игра может запуститься в окно – используем timeout, чтобы завершить процесс через 2 секунды
        output=$(timeout 1s "$EXEC" "$file" 2>&1)
        # Берём первую строку вывода
        first_line=$(echo "$output" | head -n1)
        
        if [ "$expected" == "good" ]; then
            if [[ $first_line == Error* ]]; then
                echo "FAIL: Карта $file неверно отвергнута (перв. строка: \"$first_line\")"
                ((fail_count++))
            else
                echo "PASS: Карта $file запустилась (первая строка: \"$first_line\")"
                ((pass_count++))
            fi
        elif [ "$expected" == "bad" ]; then
            if [[ $first_line == Error* ]]; then
                echo "PASS: Карта $file правильно отвергнута (первая строка: \"$first_line\")"
                ((pass_count++))
            else
                echo "FAIL: Карта $file должна быть ошибочной, но запустилась (первая строка: \"$first_line\")"
                ((fail_count++))
            fi
        fi
    done

    echo "----------------------------------------------------"
    echo "Итого в директории $dir: PASS = $pass_count, FAIL = $fail_count"
    echo ""
    # Если были ошибки – вернуть ненулевой статус
    if [ $fail_count -ne 0 ]; then
        return 1
    fi
    return 0
}

# Тестируем хорошие карты (ожидается, что программа не выводит "Error" на первой строке)
test_maps_in_dir "maps/good" "good"
good_result=$?

# Тестируем плохие карты (ожидается, что программа выводит "Error" на первой строке)
test_maps_in_dir "maps/bad" "bad"
bad_result=$?

if [ $good_result -eq 0 ] && [ $bad_result -eq 0 ]; then
    echo "Все тесты пройдены успешно!"
    exit 0
else
    echo "Некоторые тесты завершились с ошибкой."
    exit 1
fi
