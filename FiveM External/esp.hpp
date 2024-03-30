#pragma once 
#include "../vector.h"
#include <Windows.h>
#include <iostream>
#include <string> 
#include "../include/imgui/imgui.h"
#include "Render.hpp"
#include "include.h"
#include "include.h"
#include "offsets.h"
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

D3DXVECTOR2 world_to_screen(D3DXVECTOR3 world_pos) {
    auto viewmatrix = read_mem<D3DXMATRIX>(viewport_ptr + 0x24C);

    D3DXMatrixTranspose(&viewmatrix, &viewmatrix);
    auto vec_x = D3DXVECTOR4(viewmatrix._21, viewmatrix._22, viewmatrix._23, viewmatrix._24),
        vec_y = D3DXVECTOR4(viewmatrix._31, viewmatrix._32, viewmatrix._33, viewmatrix._34),
        vec_z = D3DXVECTOR4(viewmatrix._41, viewmatrix._42, viewmatrix._43, viewmatrix._44);

    auto screen_pos = D3DXVECTOR3((vec_x.x * world_pos.x) + (vec_x.y * world_pos.y) + (vec_x.z * world_pos.z) + vec_x.w,
        (vec_y.x * world_pos.x) + (vec_y.y * world_pos.y) + (vec_y.z * world_pos.z) + vec_y.w,
        (vec_z.x * world_pos.x) + (vec_z.y * world_pos.y) + (vec_z.z * world_pos.z) + vec_z.w);

    if (screen_pos.z <= 0.1f)
        return D3DXVECTOR2(0, 0);

    screen_pos.z = 1.0f / screen_pos.z;
    screen_pos.x *= screen_pos.z;
    screen_pos.y *= screen_pos.z;

    auto width = GetSystemMetrics(SM_CXSCREEN);
    auto height = GetSystemMetrics(SM_CYSCREEN);
    float x_temp = width / 2;
    float y_temp = height / 2;

    screen_pos.x += x_temp + float(0.5f * screen_pos.x * width + 0.5f);
    screen_pos.y = y_temp - float(0.5f * screen_pos.y * height + 0.5f);
    return D3DXVECTOR2(screen_pos.x, screen_pos.y);
}

D3DXVECTOR3 get_bone_position(uintptr_t ped_ptr, int bone_id) {
    auto matrix = read_mem<D3DXMATRIX>(ped_ptr + 0x60);
    D3DXVECTOR3 bone;
    if (offset::detectv2802) {
        bone = read_mem<D3DXVECTOR3>(ped_ptr + (0x410 + 0x10 * bone_id));
    }
    else {
        bone = read_mem<D3DXVECTOR3>(ped_ptr + (0x430 + bone_id * 0x10));
    }
    D3DXVECTOR4 transform;
    D3DXVec3Transform(&transform, &bone, &matrix);
    return D3DXVECTOR3(transform.x, transform.y, transform.z);
}

D3DXVECTOR2 GetBonePosDX9(uintptr_t ped_base,int boneid) {
    D3DXVECTOR3 bonepos = get_bone_position(ped_base, boneid);
    return world_to_screen(bonepos);
}

ImVec2 GetBonePosImVec(uintptr_t ped_base, int boneid) {
    D3DXVECTOR3 bonepos = get_bone_position(ped_base, boneid);
    D3DXVECTOR2 world = world_to_screen(bonepos);
    return ImVec2(world.x, world.y);
}

ImVec2 ConvertVec2(D3DXVECTOR2 point) {
    return ImVec2(point.x, point.y);
}

D3DXVECTOR3 ConvertDxVec(Vec3 point) {
    return D3DXVECTOR3(point.x, point.y, point.z);
}

void draw_skeleton(uintptr_t ped_base,ImColor Cor) {
    int bone_positions[][2] = {
        { 0, 7 },
        { 7, 6 },
        { 7, 5 },
        { 7, 8 },
        { 8, 3 },
        { 8, 4 }
    };
    for (int i = 0; i < 6; ++i) {
        auto bone_1 = get_bone_position(ped_base, bone_positions[i][0]);
        auto bone_2 = get_bone_position(ped_base, bone_positions[i][1]);
        D3DXVECTOR2 screen_1 = world_to_screen(bone_1);
        D3DXVECTOR2 screen_2 = world_to_screen(bone_2);
        DrawLine(ImVec2(screen_1.x, screen_1.y), ImVec2(screen_2.x, screen_2.y), Cor, 1);
    }
}

float pythag(ImVec2 src, ImVec2 dst) {
    return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
}

auto get_distance = [](double x1, double y1, double x2, double y2) {
    return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
};

void DrawEsp() {

    auto center_y = (GetSystemMetrics(SM_CYSCREEN));
    auto center_x = (GetSystemMetrics(SM_CXSCREEN));

    uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
    uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);

    for (int i = 0; i < 256; i++) {

        if (!PedList) continue;

        uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));
        auto pedType = read_mem<int>(Ped + 0x10b8) << 11 >> 25;

        if (!Ped) continue;

        if (esp_drawnpcs) {
            if (pedType != 2)
                continue;
        }

        if (localplayer != Ped) {



            ImColor SkelColor = Colors::ESPSkeleton;

            if (player_friend[i] == Ped) {
                SkelColor = ImColor(10, 10, 255, 255);
            }

            Vec3 EntPos = read_mem<Vec3>(Ped + 0x90);

            Vec3 LocPos = read_mem<Vec3>(localplayer + 0x90);

            float Health = read_mem<float>(Ped + 0x280);

            Vec3 DistanceCalculation = (LocPos - EntPos);

            double distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

            if (distance <= esp_max_distance) {

                ImVec2 Head = GetBonePosImVec(Ped, 0);
                ImVec2 Pelvis = GetBonePosImVec(Ped, 8);

                ImVec2 LeftFootpls = GetBonePosImVec(Ped, 1);
                ImVec2 RightFootpls = GetBonePosImVec(Ped, 2);

                float FootAdv = (LeftFootpls.y + RightFootpls.y) / 2;
                float height = fabs(Head.y - FootAdv) * 1.2;
                float width = height / 2.5;

                ImVec2 Ent2DPos = ConvertVec2(world_to_screen(ConvertDxVec(EntPos)));



                if (esp_corner) {
                    DrawCornerBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y + height / 1.9), ImVec2(width, height), Colors::ESPCorner, 1);
                }

                if (esp_box) {
                    DrawBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y - height / 2.11), ImVec2(width, height), Colors::ESPBox, 1);
                }

                if (filled_box) {
                    if (OnScreen(ImVec2(Ent2DPos.x - width / 2, Ent2DPos.y - height / 2))) {
                        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Ent2DPos.x - width / 2, Ent2DPos.y - height / 2.11), ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y + height / 1.9), ImColor(0, 0, 0, 50));

                    }
                }

                if (esp_skeletons) {
                    draw_skeleton(Ped, SkelColor);
                }
                
                if (esp_head) {
                    ImVec2 Heads = GetBonePosImVec(Ped, 0);
                    int CircleValue = height / 10;
                    if (CircleValue <= 10) { height / 15; }
                    MakeCircle(ImVec2(Heads.x, Heads.y), CircleValue, Colors::ESPSkeleton);
                }

                if (esp_lines) {
                    auto center_y = (GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYSCREEN)) + 15;
                    auto center_x = ((GetSystemMetrics(SM_CXSCREEN) / 2));
                    ImVec2 ss = GetBonePosImVec(localplayer, 8);
                    DrawLine(ImVec2(ss), ImVec2(Pelvis), Colors::ESPLines, 1);
                }

                if (esp_showid) {
                    std::string text = skCrypt("ID: ").decrypt() + std::to_string(static_cast<int>(i));
                    float font_size = 18 * text.size() / 2;
                    DrawText2d(ImVec2(Head), Colors::ESPDistance, text.c_str());
                    //FilledBox(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height), ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height / 4),ImColor(255,255,255));
                }


                if (esp_hpbar) {
                    float HealthPercentage = height / 100 * (Health);
                    float fixedhealth = Health - 100;
                    ImColor col;
                    if (fixedhealth >= 320 && fixedhealth <= 410) {
                        col = ImColor(81, 252, 141, 255);
                    }
                    else if (fixedhealth <= 320 && fixedhealth >= 240) {
                        col = ImColor(191, 245, 64, 255);
                    }
                    else if (fixedhealth <= 240 && fixedhealth >= 150) {
                        col = ImColor(221, 245, 64, 255);
                    }
                    else if (fixedhealth <= 150 && fixedhealth >= 60) {
                        col = ImColor(245, 79, 64, 255);
                    }
                    else if (fixedhealth <= 60 && fixedhealth >= 0) {
                        col = ImColor(81, 252, 141, 255);
                    }
                    else {
                        col = ImColor(81, 252, 141, 255);
                    }
                    DrawHealthBar(ImVec2(Ent2DPos.x + (width / 1.87), Ent2DPos.y + height / 1.9), ImVec2(4, (height / 100 * (100))), ImColor(10, 10, 10, 255), 2);
                    DrawHealthBar(ImVec2(Ent2DPos.x + (width / 1.87), Ent2DPos.y + height / 1.9), ImVec2(4, (HealthPercentage / 4)), col, 1.5);
                }



                if (esp_hptext) {
                    std::string text = "" + std::to_string(static_cast<int>(Health)) + skCrypt(" Hp ").decrypt();
                    float font_size = 18 * text.size() / 2;
                    if (distance <= 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 14.0f, Colors::ESPHpText, true);
                    }
                    else if (distance <= 50 && distance > 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 13.0f, Colors::ESPHpText, true);
                    }
                    else if (distance <= 75 && distance > 50)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 12.0f, Colors::ESPHpText, true);
                    }
                    else if (distance <= 100 && distance > 75)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 11.0f, Colors::ESPHpText, true);
                    }
                    else
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 10.0f, Colors::ESPHpText, true);
                    }
                }

                if (esp_showdistance) {
                    std::string text = "" + std::to_string(static_cast<int>(distance)) + " m ";
                    float font_size = 18 * text.size() / 2;
                    if (distance <= 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 14.0f, Colors::ESPDistance, true);
                    }
                    else if (distance <= 50 && distance > 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 13.0f, Colors::ESPDistance, true);
                    }
                    else if (distance <= 75 && distance > 50)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 12.0f, Colors::ESPDistance, true);
                    }
                    else if (distance <= 100 && distance > 75)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 11.0f, Colors::ESPDistance, true);
                    }
                    else
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 10.0f, Colors::ESPDistance, true);
                    }
                }
            }
        }
    }
}
