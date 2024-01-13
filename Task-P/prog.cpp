#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Person {
  public:
    int id;
    vector<int> diseases;
  
    Person(int id) {
      this->id = id;
      this->diseases = vector<int>(); 
    };

    void infect(Person& person) {
      for (int i = 0; i < person.diseases.size(); i++) {
        this->diseases.push_back(person.diseases[i]);
      }
    };
};

int main()
{	
	int z;
	cin >> z;
	while(z)
	{
    int n, m;
		cin >> n >> m;
    vector<Person> people;
    for (int i = 0; i < n; i++) {
      people.push_back(Person(i));
    }
		for(int i = 0; i < m; i++)
		{
			int x, y;
      cin >> x >> y;
      people[y].diseases.push_back(x);
		}		
		z--;
	}
	return 1;
}
