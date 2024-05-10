import onnx_graphsurgeon as gs
import numpy as np
import onnx
import onnxruntime


def reset_ir_version(path):
    _opsetVersion2IRVersion = {
        1: 3,
        5: 3,
        6: 3,
        7: 3,
        8: 3,
        9: 4,
        10: 5,
        11: 6,
        12: 7,
        13: 7,
        14: 7,
        15: 8
    }

    model = onnx.load(path)
    opset = model.opset_import[0].version
    model.ir_version = _opsetVersion2IRVersion[opset]

    onnx.checker.check_model(model)
    onnx.save(model, path)


# 1)单输入，多输出
def gather_onnx(model_path, save_path, bottom_node_name, top_node_names):
    graph = gs.import_onnx(onnx.load(model_path))

    bottom_node = [node for node in graph.nodes if node.name == bottom_node_name][0]

    top_node = []
    for e in top_node_names:
        for node in graph.nodes:
            if node.name == e:
                node.outputs[0].dtype = np.float32
                top_node.append(node)
                break

    bottom_node.inputs[0].dtype = np.float32
    graph.inputs = [bottom_node.inputs[0]]

    graph.outputs = top_node[0].outputs
    if len(top_node_names) > 1:
        for i in range(1, len(top_node_names)):
            graph.outputs.append(top_node[i].outputs[0])

    graph.cleanup()
    onnx.save(gs.export_onnx(graph), save_path)
    reset_ir_version(save_path)



model_path = r"model-sim.onnx"
sava_path = r"model-sim-1.onnx"
bottom_node_name = 'Conv_0'
top_mode_name = ['Conv_198', 'Conv_217', 'Conv_236']
gather_onnx(model_path, sava_path, bottom_node_name, top_mode_name)       # 1)单输入，多输出

