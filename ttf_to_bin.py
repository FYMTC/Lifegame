with open("arial.ttf", "rb") as f:
    data = f.read()
with open("arial_ttf.h", "w") as f:
    f.write("const unsigned char arial_ttf[] = {")
    f.write(",".join(str(b) for b in data))
    f.write("};\n")
    f.write(f"const unsigned int arial_ttf_len = {len(data)};\n")