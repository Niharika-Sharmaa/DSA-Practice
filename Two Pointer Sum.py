def two_sum_sorted(numbers, target):
    left = 0
    right = len(numbers) - 1

    while left < right:
        current_sum = numbers[left] + numbers[right]

        if current_sum == target:
            return [left + 1, right + 1]
        elif current_sum < target:
            left += 1
        else:
            right -= 1

# Example usage
numbers = [2, 7, 11, 15]
target = 9

result = two_sum_sorted(numbers, target)
print("Indices:", result)
