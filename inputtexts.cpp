#include "inputtexts.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

InputTexts::InputTexts() { text_edit_event = new TextEditEvent; }
InputTexts::InputTexts(std::string _str_id, ImVec2 _pos, ImVec2 _size, ImU32 _color_dark, ImU32 _color_light, ImU32 _color_edge, int _type, GLuint _img_email, GLuint _img_pass, GLuint _img_eye_on, GLuint _img_eye_off, float _curve) : str_id(_str_id), text(""), pos(_pos), size(_size), color_dark(_color_dark), color_light(_color_light), color_edge(_color_edge), type(_type), img_email(_img_email), img_pass(_img_pass), img_eye_on(_img_eye_on), img_eye_off(_img_eye_off), curve(_curve)
{
    text_edit_event = new TextEditEvent;
    status = false;
}

InputTexts::~InputTexts() {
}
InputTexts& InputTexts::operator = (const InputTexts& other) {
    if (this == &other)
        return *this;
    str_id = other.str_id;
    text = other.text;
    pos = other.pos, size = other.size;
    color_dark = other.color_dark, color_light = other.color_light, color_edge = other.color_edge;
    type = other.type;
    status = other.status;
    img_email = other.img_email, img_pass = other.img_pass, img_eye_on = other.img_eye_on, img_eye_off = other.img_eye_off;
    curve = other.curve;
    text_edit_event = other.text_edit_event;
    return *this;
}
void InputTexts::render(ImVec2 _pos, ImVec2 _size, ImColor bg_color) {
    pos = _pos;
    size = _size;
    float padding_x = 20;
    float padding_y = (ImGui::GetFontSize() - ImGui::GetStyle().FramePadding.y) * 2;
    float width = (size.x - padding_x * 3);
    ImVec2 start_pos = { pos.x + padding_x, pos.y + (size.y - padding_y) / 2 };
    char placeholder[30];
    char temptext[30];
    ImGui::SetCursorPos({ start_pos.x + padding_y, start_pos.y });
    ImGui::SetNextItemWidth(width - padding_y);

    if (type == 0) { strcpy(placeholder, "Email"); }
    else { strcpy(placeholder, "********"); }
    strcpy(temptext, text.data());
    int text_len = text.length();
    if (type == 1 && status == false) {
        for (int i = 0; i < text_len; ++i) { temptext[i] = '*'; }
    }
    char before[30];
    strcpy(before, text.data());
    ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(
        { start_pos.x - curve, start_pos.y - curve }, { start_pos.x + width + 20 + curve, start_pos.y + padding_y + curve },
        bg_color, color_dark, color_light, color_light, color_dark, curve);
    ImGui::GetWindowDrawList()->AddRect({ start_pos.x - curve - 1, start_pos.y - curve - 1 },
        { start_pos.x + width + 20 + curve + 2, start_pos.y + padding_y + curve + 2 },
        color_edge, curve, 0, 2.0f);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, IM_COL32(102, 153, 204, 100));
    if (type == 0)
        ImGui::InputTextWithHint(str_id.data(), placeholder, text.data(), 30);
    else
    {
        if (status == false)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 0));
            ImGui::InputTextWithHint(str_id.data(), placeholder, text.data(), 30, ImGuiInputTextFlags_Password);
            ImGui::PopStyleColor();
            ImGui::SetCursorPos({ start_pos.x + padding_y + 8, start_pos.y + 12 });
            ImGui::Text(temptext);
        }
        else
        {
            ImGui::InputTextWithHint(str_id.data(), placeholder, text.data(), 30);
        }
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    if (strcmp(before, text.data()) != 0)
        text_edit_event->OnEvent({ text.data() });

    ImGui::SetCursorPos({ start_pos.x + padding_y + 8, start_pos.y + 8 });
    
    if (type == 0)
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)img_email, start_pos, start_pos + ImVec2(padding_y, padding_y));
    else {
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)img_pass, start_pos, start_pos + ImVec2(padding_y, padding_y));
        ImGui::SetCursorScreenPos({ start_pos.x + width + 20 - padding_y, start_pos.y });
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x00, 0x00, 0x00, 0x00));
        if (status == true) {
            if (ImGui::ImageButton("##eye_on", (void*)(intptr_t)img_eye_on, { padding_y - 3, padding_y - 3 })) { status = false; }
        }
        else {
            if (ImGui::ImageButton("##eye_off", (void*)(intptr_t)img_eye_off, { padding_y - 3, padding_y - 3 })) { status = true; }
        }
        ImGui::PopStyleColor();
    }
}