#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *MakeList(const std::vector<int> &numbers) {
  ListNode *head = nullptr;
  for (auto iter = numbers.rbegin(); iter != numbers.rend(); ++iter) {
    head = new ListNode{*iter, head};
  }

  return head;
}

void PrintList(ListNode *head) {
  for (ListNode *node = head; node; node = node->next) {
    cout << node->val << ' ';
  }
}

class Solution {
 public:
  /**
   * Constraints:
   * The number of nodes in the list is sz.
   * 1 <= sz <= 30
   * 0 <= Node.val <= 100
   * 1 <= n <= sz
   */
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *result = head;
    if (head) {
      ListNode *slow = head, *fast = head->next;
      int size = 1;
      while (fast) {
        slow = Next_(slow, 1);
        if (auto next = Next_(fast, 1)) {
          fast = Next_(next, 1);
          size += 2;
        } else {
          fast = next;
          ++size;
        }
      }

      int k = size - n;
      ListNode *anchor = nullptr;
      if (k <= size / 2) {
        anchor = head;
      } else {
        anchor = slow;
        k -= size / 2;
      }
      if (0 == k) {
        result = head->next;
        delete head;
      } else {
        ListNode *prev = anchor;
        for (; 1 < k; --k) {
          prev = Next_(prev, 1);
        }
        ListNode *erased = prev->next;
        ListNode *next = erased->next;
        prev->next = erased->next;
        delete erased;
      }
    }

    return result;
  }

 private:
  ListNode *Next_(ListNode *node, int n) {
    while (0 < n-- && node) {
      node = node->next;
    }

    return node;
  }
};

void AssertEq(ListNode *lhs, ListNode *rhs) {
  cout << "left: "s;
  PrintList(lhs);
  cout << endl;
  cout << "Right: "s;
  PrintList(rhs);
  cout << endl;
  while (lhs) {
    assert(rhs);
    assert(lhs->val == rhs->val);
    lhs = lhs->next;
    rhs = rhs->next;
  }
}

void TestRemoveNthFromEnd_ListSizeIsEven() {
  Solution s;
  {
    // remove head
    auto head = MakeList({1, 2, 3, 4, 5, 6});
    head = s.removeNthFromEnd(head, 6);
    AssertEq(MakeList({2, 3, 4, 5, 6}), head);
  }
  {
    // remove from first half
    auto head = MakeList({1, 2, 3, 4, 5, 6});
    head = s.removeNthFromEnd(head, 4);
    AssertEq(MakeList({1, 2, 4, 5, 6}), head);
  }
  {
    // remove from second half
    auto head = MakeList({1, 2, 3, 4, 5, 6});
    head = s.removeNthFromEnd(head, 2);
    AssertEq(MakeList({1, 2, 3, 4, 6}), head);
  }
}

void TestRemoveNthFromEnd_ListSizeIsOdd() {
  Solution s;
  {
    // remove head
    auto head = MakeList({1, 2, 3, 4, 5});
    head = s.removeNthFromEnd(head, 5);
    AssertEq(MakeList({2, 3, 4, 5}), head);
  }
  {
    // remove from first half
    auto head = MakeList({1, 2, 3, 4, 5});
    head = s.removeNthFromEnd(head, 4);
    AssertEq(MakeList({1, 3, 4, 5}), head);
  }
  {
    // remove from second half
    auto head = MakeList({1, 2, 3, 4, 5});
    head = s.removeNthFromEnd(head, 2);
    AssertEq(MakeList({1, 2, 3, 5}), head);
  }

  {
    // remove single list node
    auto head = MakeList({1});
    head = s.removeNthFromEnd(head, 1);
    assert(head == nullptr);
  }
}

int main() {
  TestRemoveNthFromEnd_ListSizeIsEven();
  TestRemoveNthFromEnd_ListSizeIsOdd();
  std::cout << "Ok!" << std::endl;
  return 0;
}
