#pragma once

template <typename EventParam>
class Event
{
	using EVENT_FUNC = std::function<void(object, EventParam)>;
	template <typename T>
	friend class EventHandler;
private:
	EVENT_FUNC func;
public:
	__declspec(property(get = GetID)) int ID;

	Event(EVENT_FUNC _func) : func(_func)
	{

	}

	int GetID() { return (int)(this); }

	void operator()(object sender, EventParam param)
	{
		func(sender, param);
	}
};

template <typename EventParam>
class EventHandler
{
	using EVENT = Event<EventParam>;
private:
	map<int, Event<EventParam>*> eventMap;

public:
	~EventHandler() {
		for (auto iter : eventMap)
		{
			SAFE_DELETE(iter.second);
		}
		eventMap.clear();
	}

	// 이벤트 추가
	// new 해서 넣으면 알아서 삭제
	void Add(EVENT* _event)
	{
		eventMap.insert(make_pair((int)_event, _event));
	}

	bool Remove(EVENT* _event)
	{
		auto find = eventMap.find((int)_event);

		if (find == eventMap.end())
		{
			return false;
		}

		SAFE_DELETE((*find).second);
		eventMap.erase(find);

		return true;
	}

	void SafeRemove(EVENT* _event)
	{
		if (Remove(_event) == false)
		{
			SAFE_DELETE(_event);
		}
	}

	void operator ()(object sender, EventParam param)
	{
		for (auto iter : eventMap)
		{
			(*iter.second)(sender, param);
		}
	}

	void operator +=(EVENT* _event) {
		Add(_event);
	}

	void operator -=(EVENT* _event) {
		Remove(_event);
	}
};

/* o=======================================o
   Lambda를 사용해 새 이벤트를 생성합니다.
   o=======================================o*/
#define CreateEvent(paramType, Func) new Event<paramType>([&](object sender, paramType args){ Func(sender, args); })