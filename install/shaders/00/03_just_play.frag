#version 460 core

out vec4 FragColor;

in vec2 v_uv;

uniform vec2 u_resolution;

// 最大步长和最小误差
const int MAX_STEPS = 200;
const float MIN_DIST = 0.001;
const float MAX_DIST = 50.0;

// 光线方向
vec3 getRayDirection(vec2 uv) {
    vec2 p = uv * 2.0 - 1.0; // 标准化屏幕坐标 [-1, 1]
    float aspect = u_resolution.x / u_resolution.y;
    p.x *= aspect; // 修正宽高比
    return normalize(vec3(p, -1.0)); // 投影到视椎体
}

// 定义球体的 SDF
float sphereSDF(vec3 p, vec3 center, float radius) {
    return length(p - center) - radius;
}

// 定义立方体的 SDF
float boxSDF(vec3 p, vec3 center, vec3 size) {
    vec3 d = abs(p - center) - size;
    return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);
}

// 场景 SDF
float sceneSDF(vec3 p) {
    float sphereDist = sphereSDF(p, vec3(0.0, 0.0, -3.0), 1.0); // 一个半径为1的球
    float boxDist = boxSDF(p, vec3(1.5, 0.0, -3.0), vec3(0.5, 0.5, 0.5)); // 一个0.5大小的立方体
    return min(sphereDist, boxDist); // 返回最近的物体
}

// 计算表面法线
vec3 calculateNormal(vec3 p) {
    vec2 e = vec2(0.001, 0.0);
    return normalize(vec3(
        sceneSDF(p + e.xyy) - sceneSDF(p - e.xyy),
        sceneSDF(p + e.yxy) - sceneSDF(p - e.yxy),
        sceneSDF(p + e.yyx) - sceneSDF(p - e.yyx)
    ));
}

// 光线步进
float rayMarch(vec3 ro, vec3 rd) {
    float dist = 0.0; // 当前累积距离
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 p = ro + rd * dist; // 当前光线位置
        float d = sceneSDF(p); // 距离最近物体表面的距离
        if (d < MIN_DIST) {
            return dist; // 光线与物体表面相交
        }
        if (dist > MAX_DIST) {
            break; // 超出最大步长
        }
        dist += d; // 推进光线
    }
    return -1.0; // 未命中
}

// 光照
vec3 shading(vec3 p, vec3 lightDir) {
    vec3 normal = calculateNormal(p);
    float diff = max(dot(normal, lightDir), 0.0); // 漫反射
    return vec3(1.0, 0.5, 0.2) * diff; // 简单的颜色
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution; // 标准化 UV 坐标
    vec3 rayDir = getRayDirection(uv); // 光线方向
    vec3 rayOrigin = vec3(0.0, 0.0, 2.0); // 光线起点（相机位置）

    float t = rayMarch(rayOrigin, rayDir); // 光线步进
    vec3 color = vec3(0.23, 0.21, 0.21); // 背景色

    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0)); // 光源方向
    if (t > 0.0) {
        vec3 hitPoint = rayOrigin + rayDir * t; // 光线命中点
        color = shading(hitPoint, lightDir); // 着色
    }

    FragColor = vec4(color, 1.0);
}