#pragma once

#include "includes.hpp"
#include "Classes.hpp"
#include "Settings.hpp"
#include <basetsd.h>
#include "aimbot.hpp"
static float noclipspeed = 1.00001f;
static bool speed = false;


namespace NoClip
{
	void Hook(void)
	{
		if (Settings::Player::NoClip)
		{
			hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
			if (!Nav)
				return;

			Vector3 ActualPos = LocalPlayer->GetCoordinate();

			if (LocalPlayer->IsInAVehicule() == true)
			{
				return;
			}
			if (LocalPlayer->GetHealth() < 100)return;

			if (SAFE_CALL(GetAsyncKeyState)(VK_LSHIFT))
				speed = true;
			else
				speed = false;

			if (Settings::Player::NoClipSpeed_bool)
			{
				if (speed)
				{
					noclipspeed = Settings::Player::Speed;
				}
				else
				{
					noclipspeed = Settings::Player::Speed;
				}
			}
			else {

				if (speed)
				{
					noclipspeed = 1.0f;
				}
				else
				{
					noclipspeed = 0.1f;
				}
			}

			if (SAFE_CALL(GetAsyncKeyState)(Settings::misc::NoclipKey))
			{
				Settings::Player::isNoclipWorking = !Settings::Player::isNoclipWorking;
			}
			else {

				Settings::Player::isNoclipWorking;
			}

			if (Settings::Player::isNoclipWorking)
			{
				Nav->SetRotation(Vector4(0, 0, 0, 0));

				if (SAFE_CALL(GetAsyncKeyState)(Settings::Player::ForwardHotkey) & 0x8000)
				{
					LocalPlayer->SetVelocity();

					DWORD64 addr = FiveM::GetCamera();
					Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
					if (TPSangles == Vector3(0, 0, 0))
					{
						TPSangles = *(Vector3*)(addr + 0x40);
					}
					Vector3 newpos = ActualPos;
					newpos.x += (TPSangles.x * noclipspeed);
					newpos.y += (TPSangles.y * noclipspeed);
					newpos.z += (TPSangles.z * noclipspeed);
					LocalPlayer->SetCoordinate(newpos);
					Nav->SetCoordinate(newpos);
				}

				if (SAFE_CALL(GetAsyncKeyState)(Settings::Player::BackwardHotkey) & 0x8000)
				{
					LocalPlayer->SetVelocity();
					DWORD64 addr = FiveM::GetCamera();
					Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
					if (TPSangles == Vector3(0, 0, 0))
					{
						TPSangles = *(Vector3*)(addr + 0x40);
					}
					Vector3 newpos = ActualPos;
					newpos.x -= (TPSangles.x * noclipspeed);
					newpos.y -= (TPSangles.y * noclipspeed);
					newpos.z -= (TPSangles.z * noclipspeed);
					LocalPlayer->SetCoordinate(newpos);
					Nav->SetCoordinate(newpos);
				}
			}
		}
	}
}
