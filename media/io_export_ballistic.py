bl_info = {
    "name":         "Ballistic XML",
    "author":       "Luciano da Silva",
    "blender":      (2,6,2),
    "version":      (0,0,1),
    "location":     "File > Import-Export",
    "description":  "Export custom data format",
    "category":     "Import-Export"
}
        
import bpy
from bpy_extras.io_utils import ExportHelper

# -------------------------------------------------------
# export model
# -------------------------------------------------------
def write_vertices(mesh, output_file):
    output_file.write ("       <position>");
    first = True;
    for vert in mesh.vertices:
        for v in vert.co:
            if first:
                first = False;
            else:
                output_file.write (",");
            output_file.write("%f" % v);

    output_file.write ("</position>\n");

def write_normal(mesh, output_file):
    output_file.write ("        <normal>");
    first = True;
    for vert in mesh.vertices:
        for v in vert.normal:
            if first:
                first = False;
            else:
                output_file.write (",");
            output_file.write ("%f" % v);

    output_file.write ("</normal>\n");

def write_uv(mesh, output_file):
    output_file.write ("        <uv>");

    uv_layer = mesh.uv_layers.active.data;

    first = True;
    for poly in mesh.polygons:
        for loop_index in range (poly.loop_start, poly.loop_start + poly.loop_total):
            for v in uv_layer [loop_index].uv:
                if first:
                    first = False;
                else:
                    output_file.write (",");
                output_file.write ("%f" % v);
    output_file.write ("</uv>\n");


def write_indexes(mesh, output_file):
    output_file.write ("        <index>");
    first = True;
    for poly in mesh.polygons:
        for loop_index in range (poly.loop_start, poly.loop_start + poly.loop_total):
            if first:
                first = False;
            else:
                output_file.write (",");
            output_file.write ("%i" % mesh.loops [loop_index].vertex_index);
    output_file.write ("</index>\n");

def write_model (mesh, output_file):
    output_file.write ("   <mesh name=\"%s\">\n" % obj.name);

    write_indexes (obj.data, output_file);
    write_vertices (obj.data, output_file);
    write_normal (obj.data, output_file);
    write_uv (obj.data, output_file);

    output_file.write ("   </mesh>\n");

# -------------------------------------------------------

class ExportMyFormat(bpy.types.Operator, ExportHelper):
    bl_idname       = "export_my_format.xml";
    bl_label        = "Ballistic Model Data Exporter";
    bl_options      = {'PRESET'};
    
    filename_ext    = ".xml";

    # -------------------------------------------------------



    # -------------------------------------------------------

    # -------------------------------------------------------
    
    def execute(self, context):

        bpy.ops.object.mode_set(mode='OBJECT');

        scene = context.scene;
        selection = [];

        for ob in scene.objects:
            if ob.is_visible(scene) and ob.select and ob.type == 'MESH':
                selection.append (ob);
        
        if len (selection) != 1:
            raise NameError ("A single mesh object should be selected for export");

        obj = selection[0];

        out_file = open (self.filepath, 'w');
        out_file.write ("<package>\n");
        
        write_model (obj.data, out_file);

        out_file.write ("</package>\n");
        out_file.close ();
        return {'FINISHED'};

def menu_func(self, context):
    self.layout.operator(ExportMyFormat.bl_idname, text="Ballistic Model Format(.xml)");

def register():
    bpy.utils.register_module(__name__);
    bpy.types.INFO_MT_file_export.append(menu_func);
    
def unregister():
    bpy.utils.unregister_module(__name__);
    bpy.types.INFO_MT_file_export.remove(menu_func);

if __name__ == "__main__":
    register()
