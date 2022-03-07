#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <random>
#include <unordered_map>
// MERGE SORT ALGORITHM VISUALIZATION
#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
class Obj {
private:
	std::unique_ptr <sf::RenderWindow> window1;
	sf::VideoMode window;
	std::vector<float> nums1;
	std::unordered_map<float, sf::RectangleShape> shape;
	sf::Event event;
public:
	Obj();
	~Obj();
	void Update();
	void InitWindow();
	void PollEvent();
	void InitSquare(std::vector<float>& nums);
	void draw();
	const bool isOpen() const;
	void sort(std::vector<float>& nums1);
};

void Obj::Update() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	sort(nums1);
}

const bool Obj::isOpen() const
{
	return window1->isOpen();
}


Obj::~Obj()
{

}

void Obj::PollEvent() {
	while (window1->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window1->close();
			break;


		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window1->close();
				break;
			}
		}
	}
}

void Obj::InitWindow() {
	window.height = 800;
	window.width = 1400;
	window1 = std::make_unique <sf::RenderWindow>(window, "Sorting Algorithms", sf::Style::Titlebar | sf::Style::Close);
	window1->setFramerateLimit(60);
}

void Obj::InitSquare(std::vector<float>& nums) {
	nums1 = nums;
	const float distance = window.width / nums.size();//+ 0.01f;
	float countup = 0.f;
	for (int i = 0; i < nums.size(); i++)
	{
		sf::RectangleShape col;
		col.setFillColor(sf::Color::White);
		col.setSize(sf::Vector2f(distance, nums[i]));
		col.setPosition(sf::Vector2f(countup, window.height - nums[i]));
		auto b = std::make_pair(nums[i], col);
		shape.insert(b);
		countup +=  distance;
	}
}

void Obj::draw() {
	window1->clear(sf::Color::Black);
	for (auto& i : shape) {
		window1->draw(i.second);
	}
	window1->display();
}

void Obj::sort(std::vector<float>& nums1)
{
	if (nums1.size() == 1)
	{
		return;
	}

	std::vector <float> left;
	std::vector <float> right;

	{
		for (int i = 0; i < nums1.size() / 2; i++)
		{
			left.push_back(nums1[i]);
		}
		for (int i = nums1.size() / 2; i < nums1.size(); i++)
		{
			right.push_back(nums1[i]);
		}
	}

	std::unordered_map<float, float> recurse;
	for (int i = 0; i < nums1.size(); i++)
	{
		auto a = std::make_pair(nums1[i], shape[nums1[i]].getPosition().x);
		recurse.insert(a);
	}

	sort(left);
	sort(right);

	left.push_back(pow(10, 5));
	right.push_back(pow(10, 5));

	int a = 0, b = 0;
	for (int i = 0; i < nums1.size(); i++)
	{
		
		if (left[a] >= right[b])
		{
			shape[right[b]].setPosition(sf::Vector2f(recurse[nums1[i]], window.height - shape[right[b]].getSize().y));
			nums1[i] = right[b];
			window1->clear(sf::Color::Black);
			for (auto& i : shape) {
				window1->draw(i.second);
			}
			window1->display();
			b++;
		}

		else if (right[b] >= left[a])
		{
			shape[left[a]].setPosition(sf::Vector2f(recurse[nums1[i]], window.height - shape[left[a]].getSize().y));
			nums1[i] = left[a];
			window1->clear(sf::Color::Black);
			for (auto& i : shape) {
				window1->draw(i.second);
			}
			window1->display();
			a++;
		}
	}
	return;
}

Obj::Obj() {
	InitWindow();
}

int main() {
	Obj obj;
	std::vector<float> nums;
	//float input;
	//std::cin >> input;
	for (float i = 0; i < 700; i++)
	{
		nums.push_back(i);
	}
	
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(nums.begin(), nums.end(), g);
	obj.InitSquare(nums);
	
	while (obj.isOpen())
	{
		obj.PollEvent();
		obj.Update();
		obj.draw();
	}
	return 0;
}
