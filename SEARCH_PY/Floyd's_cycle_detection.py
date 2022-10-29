"""Алгоритм поиска зацикленности списка - Floyd's_cycle_detection"""
class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next

def detect_cycle(head):
    slow = head                 # Медленный указатель
    fast = head                 # Быстрый указатель

    while fast and fast.next:   # Пока указывают не null
        slow = slow.next        # Сдвинуть на шаг вперед
        fast = fast.next.next   # Сдвинуть на 2 шага вперед
        if slow == fast:        # Если адреса сравнялись, значит есть зацикленность
            return True
    return False                # Иначе список не замыкается на себе


if __name__ == '__main__':

    head = None
    for i in reversed(range(5)):
        head = Node(i + 1, head)
    # Создание зацикленности
    head.next.next.next.next.next = head.next.next
    print("Cycle found") if detect_cycle(head) else print("No cycle found")