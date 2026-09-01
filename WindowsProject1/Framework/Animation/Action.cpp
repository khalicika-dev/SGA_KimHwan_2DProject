#include "Framework.h"
#include "Action.h"

Action::Action(vector<Clip> clips, Type type, Delegate endEvent)
: _clips(clips)
, _repeatType(type)
, _curClipNo(0)
, _isPlay(true)
, _time(0.0f)
, _isReverse(false)
, _endEvent(endEvent)
{
}

Action::~Action()
{
}

void Action::Update()
{
	if (!_isPlay)
		return;

	_time += DELTATIME;

	if (_time > _clips[_curClipNo].speed)
	{
		switch (_repeatType)
		{
		case Action::END:
		{
			_curClipNo++;
			if (_curClipNo >= _clips.size())
				Stop();
			break;
		}
		case Action::LOOP:
		{
			_curClipNo++;
			_curClipNo %= _clips.size();
			break;
		}
		case Action::PINGPONG:
		{
			if (_isReverse)
			{
				_curClipNo--;
				if (_curClipNo <= 0)
					_isReverse = false;
			}
			else
			{
				_curClipNo++;
				if (_curClipNo >= _clips.size() - 1)
					_isReverse = true;
			}
			break;
		}
		default:
			break;
		}

		_time = 0.0f;
	}
}

void Action::Play()
{
	_isPlay = true;
	_isReverse = false;
	_time = 0.0f;
	_curClipNo = 0;
}

void Action::Pause()
{
	_isPlay = false;
}

void Action::Stop()
{
	_isPlay = false;
	if (_endEvent)
	{
		_curClipNo = _clips.size() - 1;
		_endEvent();
	}
	else
		_curClipNo = _clips.size() - 1;
}

void Action::gotoStop(UINT ClipNo)
{
	_isPlay = false;
	_isReverse = false;
	_time = 0.0f;
	_curClipNo = ClipNo;
}